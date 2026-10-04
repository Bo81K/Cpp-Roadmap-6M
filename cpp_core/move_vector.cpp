#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec;

    std::cout << "push_back с копированием\n";
    std::string text = "Hello, Wold! This is long string.";
    vec.push_back(text);
    std::cout << "text после копирования: " << text << "\n";
    std::cout << "vec[0]: " << vec[0] << "\n";

    std::cout << "push_back с перемещением\n";
    std::string text2 = "Another looooooooooong string.";
    vec.push_back(std::move(text2));
    std::cout << "text2 после перемещения: " << text2 << "\n";
    std::cout << "vec[1]: " << vec[1] << "\n";

    std::cout << "emplace_back создаёт на месте\n";
    vec.emplace_back("Created directly inside vector");
    std::cout << "vec[2]: " << vec[2] << "\n";

    return 0;
}