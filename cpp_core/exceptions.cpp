#include <iostream>
#include <stdexcept>

double safeDivide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero!");
    }
    return a/b;
}

int main() {
    try{
        double result = safeDivide (10.0, 2.0);
        std::cout << "10/2 = " << result << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        double result = safeDivide(10.0, 0.0);
        std::cout << "10 / 0 = " << result << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}

/*
exception - базовый класс всех стандартных исключений,
runtime_error - его наследник, поэтому он срабатывает.

Когда пишем throw, программа прерывает нормальное выполнение и ищет ближайший catch.
Если catch есть - ошибка обрабатывается, и программа продолжает работать.
Если catch нет - программа падает полностью 
*/