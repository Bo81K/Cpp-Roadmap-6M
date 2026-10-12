#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int count = 0;


    std::for_each(numbers.begin(), numbers.end(), [&count](int n){
        if (n % 2 == 0){
            count++;
        }
    });

    std::cout << "Количество чётных: " << count << "\n";

    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int n){
        sum += n;
    });

    std::cout << "Сумма: " << sum << "\n";

    int threshold = 5;
    int count_t = 0;
    
    std::vector<int> nums = {1, 3, 7, 2, 9, 4, 8};
    
    // считаем числа больше              threshold - по умолчанию константа так как не &
    std::for_each(nums.begin(), nums.end(), [threshold, &count_t](int n) {
        if (n > threshold) {
            count_t++;
        }
    });
    
    std::cout << "Чисел больше " << threshold << ": " << count_t << "\n";
    
    return 0;
}
/*
Захват [=] и [&] работает только с переменными,
у которых автоматический срок хранения
(локальные переменные, параметры функций)

[=]  // Захватить ВСЕ внешние переменные ПО ЗНАЧЕНИЮ
[&]  // Захватить ВСЕ внешние переменные ПО ССЫЛКЕ
[=, &x]  // Всё по значению, кроме x (по ссылке)
[&, x]   // Всё по ссылке, кроме x (по значению)
*/