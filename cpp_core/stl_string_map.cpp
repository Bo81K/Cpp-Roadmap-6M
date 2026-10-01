#include <iostream>
#include <string>
#include <map>

int main() {
    std::cout << "std::string\n";
    // по сути string это vector<char> со своими удобными методами
    std::string name = "Hello";
    name += ", World!"; //конкатенация

    std::cout << "String: " << name << "\n";
    std::cout << "Length: " << name.length() << "\n";
    // тоже без проверки границ, как в массиве
    std::cout << "First char: " << name[0] << "\n";

    // проверка подстроки
    if (name.find("World") != std::string::npos) {
        std::cout << "Found 'World'!\n";
    }

    std::cout << "std::map\n";
    // map хранит пары ключ-значение, отсортированные по ключу
    // ключ std::string, значение int
    std::map<std::string, int> ages;
    
    //map автоматически отсортирует ключи в алфавитном порядке
    ages["Chad"] = 22;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    
    // обращение по ключу
    std::cout << "Alice is " << ages["Alice"] << "\n";

    // обход словаря
    // std::pair - структура из полей first и second
    for (const auto& pair : ages) {
        std::cout << pair.first << " is " << pair.second << " years old\n";
    }

    // проверка наличия ключа
    if (ages.count("Bob") > 0){
        std::cout << "Bob exists in the map!\n";
    }

    return 0;
}