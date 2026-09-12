#include <iostream>
#include <cstring>
#include <utility>

class MyString
{
    char *data;
    size_t size;

public:
    MyString(const char *str = ""){
        size = std::strlen(str);
        data = new char[size + 1];
        std::strcpy(data, str);
    };

    ~MyString(){
        delete[] data;
    };

    MyString(const MyString &other){
        size = other.size;
        data = new char[size + 1];
        std::strcpy(data, other.data);
    }

    MyString &operator = (const MyString &other){
        if(this == &other) return *this;
        MyString tmp(other);
        std::swap(this->data, tmp.data);
        std::swap(this->size, tmp.size);
        return *this;
    }

    MyString (MyString &&other) noexcept{
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }

    MyString &operator=(MyString &&other) noexcept{
        if(this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    const char * c_str() const{
        return data;
    }
    size_t length() const{
        return size;
    }
};

int main() {
    // 1. Создание из строкового литерала
    MyString s1("Hello");
    std::cout << "s1: " << s1.c_str() << " (len=" << s1.length() << ")\n";

    // 2. Копирование
    MyString s2 = s1;               // вызов конструктора копирования
    std::cout << "s2 (copy of s1): " << s2.c_str() << "\n";

    // 3. Присваивание копированием
    MyString s3;
    s3 = s1;                        // вызов оператора присваивания
    std::cout << "s3 (assigned from s1): " << s3.c_str() << "\n";

    // 4. Перемещение (конструктор перемещения)
    MyString s4 = std::move(s1);    // s1 больше не должен использоваться
    std::cout << "s4 (moved from s1): " << s4.c_str() << "\n";
    // s1 теперь пуст, его c_str() может быть nullptr - не выводим его!

    // 5. Присваивание перемещением
    MyString s5;
    s5 = std::move(s2);             // s2 опустошается
    std::cout << "s5 (move-assigned from s2): " << s5.c_str() << "\n";

    // 6. Передача в функцию по значению (копирование) и возврат (перемещение)
    auto make_string = []() {
        MyString temp("Temporary");
        return temp;   // перемещение при возврате (NRVO или move)
    };
    MyString s6 = make_string();
    std::cout << "s6 (from function): " << s6.c_str() << "\n";

    return 0;
}
