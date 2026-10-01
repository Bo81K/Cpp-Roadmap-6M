#include <iostream>
#include <vector>
#include <algorithm> // для std::sort, std::find_if, std::count_if
#include <numeric> // для std::accumulate

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    std::cout << "Original: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    std::cout << "Сортировка\n";

    //std::sort принимает начало и конец диапазона
    std::sort(numbers.begin(), numbers.end());

    std::cout << "Sorted: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout <<"\n";

    std::cout << "Сортировка лямбдой (по убыванию)\n";
    // третий аргумент - лямбда, которая определяет порядок сортировки
    std::sort(numbers.begin(), numbers.end(), [](int a, int b){
        return a > b;// a должен стоять перед b если a больше b
    });

    std::cout << "Sorted descending: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout <<"\n";

    std::cout << "Поиск с условием\n";

    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n){
        return n > 5;
    });

    if(it != numbers.end()){
        std::cout << "First number > 5: " << *it << "\n";
    }

    std::cout << "подсчёт с условием\n";
    // посчитать количество чётных чисел
    int evenCount = std::count_if(numbers.begin(), numbers.end(), [](int n){
        return n % 2 == 0;
    });

    std::cout << "Even numbers count: " << evenCount << "\n";

    std::cout << "Сумма всех элементов\n";

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << "\n";

    std::cout << "Захват переменных в лямбде\n";

    int threshold = 6;
    int countAbove = std::count_if(numbers.begin(), numbers.end(), [threshold](int n){
        return n > threshold;
    });

    std::cout << "Numbers > " << threshold << ": " << countAbove << "\n";

    return 0;
}