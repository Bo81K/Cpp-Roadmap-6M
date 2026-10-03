#include <iostream>
#include <string>

template <typename T>
void mySwap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T myMax (T a, T b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

template <typename T>
T myAbs(T x){
    if(x > 0){
        return x;
    } else {
        return -x;
    }
}

int main() {
    // Тест mySwap
    int x = 10, y = 20;
    std::cout << "Before swap: x=" << x << ", y=" << y << "\n";
    mySwap(x, y);
    std::cout << "After swap: x=" << x << ", y=" << y << "\n";

    // Тест mySwap с double
    double a = 3.14, b = 2.71;
    std::cout << "Before swap: a=" << a << ", b=" << b << "\n";
    mySwap(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << "\n";

    // Тест myMax
    std::cout << "Max(3, 7) = " << myMax(3, 7) << "\n";
    std::cout << "Max(3.14, 2.71) = " << myMax(3.14, 2.71) << "\n";

    // Тест myMax со строками (работает, потому что string умеет operator>)
    std::string s1 = "apple", s2 = "banana";
    std::cout << "Max(apple, banana) = " << myMax(s1, s2) << "\n";

    // Тест myAbs
    std::cout << "Abs(-5) = " << myAbs(-5) << "\n";
    std::cout << "Abs(-3.14) = " << myAbs(-3.14) << "\n";

    return 0;
}