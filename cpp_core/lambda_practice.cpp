#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

struct Employee {
    std::string name;
    int age;
    double salary;
};

int main() {
    std::vector<Employee> employees = {
        {"Alice", 28, 75000},
        {"Bob", 35, 92000},
        {"Charlie", 42, 110000},
        {"Diana", 31, 85000},
        {"Eve", 26, 68000},
        {"Frank", 38, 95000},
        {"Grace", 29, 72000}
    };

    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b){
        return a.salary > b.salary; // a стоит перед b, если a больше
    });
    
    std::cout << "Топ по зарплате\n";
    for (const auto& e : employees) {
        std::cout << e.name << ": $" << e.salary << "\n";
    }

    //старше 30
    int count_age = std::count_if(employees.begin(), employees.end(), [](const Employee& a){
        return a.age > 30;
    });
    std::cout << "Старше 30: " << count_age << " человек\n";

    // Найти сотрудника с максимальной зарплатой
    auto maxIt = std::max_element(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.salary < b.salary;
    });
    if (maxIt != employees.end()) {
        std::cout << "\nМаксимальная зарплата у " << maxIt->name << ": $" << maxIt->salary << "\n";
    }

    // cредняя зарплата
    double total = 0;
    std::for_each(employees.begin(), employees.end(), [&total](const Employee& e) {
        total += e.salary;
    });
    double avg = total / employees.size();
    std::cout << "Средняя зарплата: " << avg << "\n";

    // удаление сотрудников с зарплатой ниже 70000
    int minLength = 70000;
    auto it = std::remove_if(employees.begin(), employees.end(), [minLength](const Employee& e){
        return e.salary < minLength;
    });
    employees.erase(it, employees.end());

    std::cout << "\nПосле удаления низкооплачиваемых\n";
    for (const auto& e : employees) {
        std::cout << e.name << ": $" << e.salary << "\n";
    }

    // повысить зарплату всем на 10%
    double raise = 1.10;
    std::for_each(employees.begin(), employees.end(), [raise](Employee& e) {
        e.salary *= raise;
    });

    std::cout << "\nПосле повышения на 10%\n";
    for (const auto& e : employees) {
        std::cout << e.name << ": $" << e.salary << "\n";
    }

    return 0;
}