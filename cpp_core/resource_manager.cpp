#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <thread>

// базовый класс для всех ресурсов
class Resource
{
protected:
    std::string name_;
public:
    Resource(std::string name) : name_(name){
        std::cout << "+ Resource created: " << name_ << "\n";
    }
    virtual ~Resource() {
        std::cout << "- Resource destroyed:" << name_ << "\n";
    }

    virtual void use() = 0;

    std::string getName() const {return name_;}
};

// unique_ptr 
// файл которым владеет только один объект
class FileResource : public Resource {
private:
    std::string filename_;

public:
    FileResource(std::string filename) : Resource("File: " + filename), filename_(filename) {
        std::cout << "  Opening file: " << filename_ << "\n";
    }
    ~FileResource() override { //подзабыл что значит override
        std::cout << "  Closing file: " << filename_ << "\n";
    }

    void use() override {
        std::cout << "  Reading from " << filename_ << "\n";
    }
};

// фабричная функция, возвращающая unique_ptr
// немного не понимаю, что тут происходит
std::unique_ptr<FileResource> openFile(const std::string& filename) {
    return std::make_unique<FileResource> (filename);
}

// shared_ptr - общий ресурс
// Подключение к БД, которое могут использовать несколько объектов
class DatabaseConnection : public Resource {
private:
    std::string dbUrl_;

public:
    DatabaseConnection(std::string dbUrl) : Resource("DB: " + dbUrl), dbUrl_(dbUrl){
        std::cout << "  Connecting to DB: " << dbUrl_ << "\n";
    }

    ~DatabaseConnection() override {
        std::cout << "  Disconnecting from DB: " << dbUrl_ << "\n";
    }

    void use() override {
        std::cout << "  Executing query on " << dbUrl_ << "\n";
    }

    void query(const std::string& sql){
        std::cout << "  SQL: " << sql << " on " << dbUrl_ << "\n";
    }
};

//weak_ptr - наблюдатель
// наблюдает за ресурсами, НО не владеет ими
class ResourceObserver {
private:
    std::map <std::string, std::weak_ptr<Resource>> observers_;

public:
    void watch(std::shared_ptr<Resource> resource) {
        std::string name = resource->getName();
        observers_[name] = resource; // weak_ptr автоматически создаётся из shared_ptr
        std::cout << "  👀 Now watching: " << name << "\n";
    }

    void checkStatus() {
        std::cout << "  Resource Status Check\n";
        for(auto& [name, weakPtr] : observers_) { // пытаемся получить shared_ptr
            if (auto sharedPtr = weakPtr.lock()) {
                std::cout << " OK " << name << " is alive (use_count: " 
                        << sharedPtr.use_count() << ")\n";
            } else {
                std::cout << " BRUH " << name << " is destroyed\n";
            }
        }
    }
};

// Применяем
// Сервис, использующий общие ресурсы
class UserService {
private:
    std::shared_ptr<DatabaseConnection> db_; //разделяемое владение

public:
    UserService(std::shared_ptr<DatabaseConnection> db) : db_(db) {
        std::cout << "+ UserService created\n";
    }

    ~UserService() {
        std::cout << "- UserService destroyed\n";
    }

    void findUser(int id) {
        std::cout << "  UserService finding user " << id << "\n";
        db_->query("SELECT * FROM users WHERE id = " + std::to_string(id));
    }
};

class OrderService {
private:
    std::shared_ptr<DatabaseConnection> db_;

public:
    OrderService(std::shared_ptr<DatabaseConnection> db) : db_(db) {
        std::cout << "+ OrderService created\n";
    }
    
    ~OrderService() {
        std::cout << "- OrderService destroyed\n";
    }
    
    void createOrder(int userId) {
        std::cout << "  OrderService creating order for user " << userId << "\n";
        db_->query("INSERT INTO orders (user_id) VALUES (" + std::to_string(userId) + ")");
    }
};

int main() {
    std::cout << " СЦЕНАРИЙ 1: Unique_ptr (Файлы) \n";
    {
        // Фабричная функция возвращает unique_ptr
        auto file1 = openFile("data.txt");
        auto file2 = openFile("config.json");
        
        file1->use();
        file2->use();
        
        // Нельзя скопировать:
        // auto file3 = file1;  // Ошибка компиляции
        
        // Можно переместить:
        auto file3 = std::move(file1);
        
        if (!file1) {
            std::cout << "file1 is now null (ownership transferred to file3)\n";
        }
        
        file3->use();
        
        std::cout << "\n Конец блока \n";
    }  // Все файлы автоматически закрываются здесь

    std::cout << " СЦЕНАРИЙ 2: Shared_ptr (БД) \n";
    ResourceObserver observer;
    {
        // Создаём подключение к БД
        auto dbConnection = std::make_shared<DatabaseConnection>("postgresql://localhost/mydb");
        
        // Наблюдатель следит за подключением (weak_ptr)
        observer.watch(dbConnection);
        
        std::cout << "\nUse count: " << dbConnection.use_count() << " (только dbConnection)\n";
        
        // Создаём сервисы, которые используют то же подключение
        auto userService = std::make_unique<UserService>(dbConnection);
        std::cout << "Use count: " << dbConnection.use_count() << " (dbConnection + userService)\n";
        
        auto orderService = std::make_unique<OrderService>(dbConnection);
        std::cout << "Use count: " << dbConnection.use_count() << " (dbConnection + userService + orderService)\n";
        
        // Используем сервисы
        userService->findUser(42);
        orderService->createOrder(42);
        
        // Проверяем статус через наблюдателя
        observer.checkStatus();
        
        std::cout << "\n Уничтожаем orderService \n";
        orderService.reset();  // Явно уничтожаем
        std::cout << "Use count: " << dbConnection.use_count() << " (dbConnection + userService)\n";
        
        observer.checkStatus();

        std::cout << "\n Конец блока \n";
    }  // Все shared_ptr уничтожаются, БД отключается

    std::cout << "\n Проверка после уничтожения \n";
    observer.checkStatus();  // Ресурс уже уничтожен
    
    std::cout << " СЦЕНАРИЙ 3: Полиформизм \n";    
    {
        // Вектор уникальных указателей на базовый класс
        std::vector<std::shared_ptr<Resource>> resources;
        
        resources.push_back(std::make_shared<FileResource>("log.txt"));
        resources.push_back(std::make_unique<FileResource>("temp.dat"));
        resources.push_back(std::make_shared<DatabaseConnection>("mysql://localhost/test"));
        
        std::cout << "\n Используем все ресурсы \n";
        for (const auto& res : resources) {
            res->use();
        }
        
        std::cout << "\n Конец блока \n";
    }  // Все ресурсы автоматически уничтожаются
    
    std::cout << " Программа завершена \n";    
    return 0;
}