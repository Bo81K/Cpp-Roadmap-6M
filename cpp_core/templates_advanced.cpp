#include <iostream>
#include <string>

template <typename T1, typename T2>
class Pair{
public:
    Pair(T1 first, T2 second) : first_(first), second_(second){}

    T1 first() const {return first_;}
    T2 second() const {return second_;}

    void swap(){
        if constexpr(std::is_same_v <T1,T2>){
            T2 swapBox_ = second_;
            second_ = first_;
            first_ = swapBox_;
        } else {
            std::cout << "Cannot swap: different rypes!\n";
        }
    }

    void print() const {
        std::cout << "(" << first_ << ", " << second_ << ")\n";
    }
private:
    T1 first_;
    T2 second_;
};

// ПОЛНАЯ специализация для Pair<string, string>
template <>
class Pair<std::string, std::string> {
public:
    Pair(std::string first, std::string second) 
        : first_(first), second_(second) {}

    std::string first() const { return first_; }
    std::string second() const { return second_; }

    void swap(){
        std::string swapBox_ = second_;
        second_ = first_;
        first_ = swapBox_;
    }

    void print() const {
        // строки выводим в кавычках
        std::cout << "(\"" << first_ << "\", \"" << second_ << "\")\n";
    }

private:
    std::string first_;
    std::string second_;
};

int main () {
    Pair<std::string, int> person ("Alice", 25);
    person.print();

    Pair<double, double> point(3.14, 2.71);
    point.print();

    Pair<std::string, std::string> greeting("Hello", "World");
    greeting.print();
/*как компилятор выбирает между шаблонами?
    по правилу приоритета:
    1. Сначала компилятор ищет точное совпадение (полную специализацию)
    2. Если не нашёл - использует основной шаблон*/
    std::cout << "Before swap: ";
    point.print();

    point.swap();

    std::cout << "After swap: ";
    point.print();

    std::cout << "Before swap: ";
    greeting.print();

    greeting.swap();
    
    std::cout << "After swap: ";
    greeting.print();
    return 0;
}

