#include <iostream>
#include <vector>

int main () {
    std::cout << "Создание вектора\n";

    std::vector <int> numbers;

    std::cout << "Добавляем элементы\n";

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    //numbers[100] = 5; UB

    try
    {
        numbers.at(100) = 5;
    } catch (const std::exception& e){
        std::cout << "Error: " << e.what() << "\n";
    }

    // то же самое без at следовательно без отлова исключения
    if(100 < numbers.size()) {numbers[100] = 5;}
    
    std::cout << "Size: " << numbers.size() << "\n";

    std::cout << "Обращение к элементам\n";
    
    // способ как у массива. Можно указать за границу и всё упадёт
    std::cout << "First: " << numbers[0] << "\n";

    // метод at() бросит исключение std::out_of_range, если индекс неверный
    std::cout << "Second: " << numbers.at(1) << "\n";

    std::cout << "Обход вектора\n";
    // цикл по диапазону (range-based for)
    // читается как: для каждого n в numbers
    for (int n : numbers) {
        std::cout << n << " ";
    }

    std::cout << "\n";

    std::cout << "Копирование\n";
    // здесь компилятор сам сделает глубокое копирование
    // и следовательно реализует правило трёх
    std::vector <int> copy = numbers;

    copy[0] = 999;

    std::cout << "Original: " << numbers[0] << "\n";
    std::cout << "Copy: " << copy[0] << "\n";

    std::cout << "Удаление элементов\n";

    numbers.pop_back();
    std::cout << "New size: " << numbers.size() << "\n";

    return 0;
    // деструкторы vector отработают сами, утечки памяти не будет
}