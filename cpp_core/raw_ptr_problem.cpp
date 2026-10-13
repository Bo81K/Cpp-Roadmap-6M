#include <iostream>
#include <stdexcept>

int created = 0;
int destroyed = 0;

class ExpensiveResource {
public:
    ExpensiveResource() { 
        created++;
        std::cout << "Resource created (total: " << created << ")\n"; 
    }
    
    ~ExpensiveResource() { 
        destroyed++;
        std::cout << "Resource destroyed (total: " << destroyed << ")\n"; 
    }
    
    void doWork() {
        std::cout << "Doing work...\n";
        if (rand() % 3 == 0) {
            throw std::runtime_error("Something went wrong!");
        }
    }
};

// утечка: ранний return
void leakyFunction() {
    ExpensiveResource* res = new ExpensiveResource();
    
    if (rand() % 2 == 0) {
        std::cout << "Early return!\n";
        return;  // утечка! delete не вызвался
    }
    
    delete res;
}

// утечка: исключение пробрасывается
void throwingFunction() {
    ExpensiveResource* res = new ExpensiveResource();
    res->doWork();  // Может бросить исключение
    delete res;  // Не вызовется при исключении
}

int main() {
    std::cout << "=== Тест 1: Ранний return ===\n";
    for (int i = 0; i < 5; ++i) {
        leakyFunction();
    }
    
    std::cout << "\n=== Тест 2: Исключение ===\n";
    for (int i = 0; i < 5; ++i) {
        try {
            throwingFunction();
        } catch (const std::exception& e) {
            std::cout << "Caught: " << e.what() << "\n";
            // утечка! Исключение поймали, но delete не вызвался
        }
    }
    
    std::cout << "\n    Итог\n";
    std::cout << "Создано: " << created << "\n";
    std::cout << "Уничтожено: " << destroyed << "\n";
    std::cout << "утечка: " << (created - destroyed) << " объектов\n";
    
    return 0;
}