#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> words = {"cat", "elephant", "dog", "butterfly", "ant"};

    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b){
        return a.length() < b.length();
    });

    std::cout << "Сортировка по длине:\n";
    for (const auto& w : words) {
        std::cout << w << " (" << w.length() << ")\n";
    }

    size_t minLength = 4;

    auto it = std::remove_if(words.begin(), words.end(), [minLength](const std::string& w){
        return w.length() < minLength;
    });

    words.erase(it, words.end());

    std::cout << "\nСлова длиннее " << minLength << ":\n";
    for (const auto& w : words) {
        std::cout << w << " (" << w.length() << ")\n";
    }

    
    auto filter = [minLength](const std::string& w) {
        return w.length() < minLength;
    };
    
    minLength = 10;  // изменили после создания лямбды
    
    std::cout << "\nПосле изменения minLength:\n";
    for (const auto& w : words) {
        if (filter(w)) {
            std::cout << w << " (удаляется)\n";
        } else {
            std::cout << w << " (остаётся)\n";
        }
    }
    
    return 0;
}