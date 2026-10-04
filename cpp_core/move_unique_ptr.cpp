#include <iostream>
#include <memory>
#include <string>

int main() {
    std::cout << "unique_ptr и перемещение\n";

    std::unique_ptr<std::string> ptr1 = std::make_unique<std::string>("Hello from ptr1");

    std::cout << "ptr1: " << *ptr1 << "\n";

    std::unique_ptr<std::string> ptr2 = std::move(ptr1);

    std::cout << "После перемещения:\n";

    if (ptr1 == nullptr) {
        std::cout << "ptr1: nullptr (передали владение)\n";
    }

    std::cout << "ptr2: " << *ptr2 << "\n";

    // std::unique_ptr нельзя скопировать (он владеет памятью единолично)
    // std::unique_ptr<std::string> ptr3 = ptr2;  // ОШИБКА КОМПИЛЯЦИИ

    std::unique_ptr<std::string> ptr3 = std::move(ptr2);
    std::cout << "ptr3: " << *ptr3 << "\n";

    return 0;
}
