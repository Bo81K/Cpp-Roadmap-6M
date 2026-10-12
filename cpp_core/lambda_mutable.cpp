#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // mutable с захватом по значению
    std::cout << "Счётчик вызовов\n";
    // инициализация внутри лямбды
    auto counter = [calls = 0]() mutable {
        calls++;
        std::cout << "Вызов - " << calls << "\n";
        return calls;
    };
    
    counter();
    counter();
    counter();
    
    std::cout << "\nАккумулятор\n";
    
    auto accumulator = [sum = 0](int value) mutable {
        sum += value;
        std::cout << "Добавили " << value << ", сумма = " << sum << "\n";
        //return sum; - если бы мы хотели использовать вне лямбды
    };
    
    accumulator(10);
    accumulator(20);
    accumulator(30);
    
    // подводный камень - лямбда сбрасывается при копировании
    std::cout << "\nКопирование лямбды\n";
    
    auto original = [count = 0]() mutable {
        count++;
        std::cout << "original: " << count << "\n";
    };
    
    auto copy = original;  // копируем лямбду
    
    original();
    original();
    
    copy();
    copy();
    
    return 0;
}

/* ВЫВОД
Счётчик вызовов
Вызов - 1
Вызов - 2
Вызов - 3

Аккумулятор
Добавили 10, сумма = 10
Добавили 20, сумма = 30
Добавили 30, сумма = 60

Копирование лямбды
original: 1
original: 2
original: 1
original: 2

*/