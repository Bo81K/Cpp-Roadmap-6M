#include <iostream>
#include <vector>
#include <cstring>

int copyCount = 0;
int moveCount = 0;

class MyString
{
private:
    char* data_ = nullptr;
    size_t size_ = 0;

public:
    MyString(const char* str){
        size_ = std::strlen(str);
        data_ = new char[size_ + 1];
        std::strcpy(data_, str);
        std::cout << "Constructor: " << data_ << "\n";
    }

    MyString(const MyString& other){
        copyCount++;
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
        std::cout << "COPY constructor: " << data_ << "\n";
    }

    MyString(MyString&& other) noexcept{
        /*Конструктор перемещения вызывается на объекте s3 (это this),
            а параметр other - это s1*/
        moveCount++;

        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;
        
        std::cout << "MOVE constructor: " << data_ << "\n";
    }

    MyString& operator = (MyString&& other) noexcept {
        moveCount++;

        if (this == &other){
            return *this;
        }

        delete[] data_;

        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;

        std::cout << "MOVE assignment: " << data_ << "\n";

        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) 
            return *this;
        copyCount++;
        
        delete[] data_;
        
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
        
        std::cout << "COPY assignment: " << data_ << "\n";
        return *this;
    }

    ~MyString(){
        std::cout << "Destructor: " << (data_ ? data_ : "(null)") << "\n";
        delete[] data_;
    }

    void print() const {
        std::cout << "data: " << (data_ ? data_ : "(null)") << "\n";
    }
};


int main(){
    MyString s1 ("Hello");
    std::cout << "Создаём копию\n";
    MyString s2 = s1;

    std::cout << "Перемещаем\n";
    MyString s3 = std::move(s1);

    std::cout << "После перемещения\n";
    std::cout << "s1: ";
    s1.print();
    std::cout << "s3: ";
    s3.print();

        std::cout << "Оператор присваивания перемещением\n";
    MyString a("Hello");
    MyString b("World");
    
    std::cout << "Before move assignment:\n";
    std::cout << "a: "; a.print();
    std::cout << "b: "; b.print();
    
    b = std::move(a);  // оператор присваивания перемещением
    
    std::cout << "After move assignment:\n";
    std::cout << "a: "; a.print();
    std::cout << "b: "; b.print();

    std::cout << "Оператор присваивания копированием\n";
    MyString c("Original");
    MyString d("Target");
    
    std::cout << "Before copy assignment:\n";
    std::cout << "c: "; c.print();
    std::cout << "d: "; d.print();
    
    d = c;  // оператор присваивания копированием
    
    std::cout << "After copy assignment:\n";
    std::cout << "c: "; c.print();
    std::cout << "d: "; d.print();
    
    std::cout << "Самоприсваивание\n";
    c = c;
    std::cout << "c after self-assignment: "; c.print();

    std::cout << "\nMyString в векторе\n";

    std::vector<MyString> vec;
    
    // при расширении вектор будет ПЕРЕМЕЩАТЬ элементы, а не копировать    
    vec.emplace_back("First");
    std::cout << "Добавляем второй (вектор расширяется)\n";
    vec.emplace_back("Second");
    
    std::cout << "\nСодержимое вектора\n";
    for (const auto& s : vec) {
        s.print();
    }

    std::cout << "Copies: " << copyCount << "\nMoves: " << moveCount << "\n";

    return 0;
}
/* Вывод
Constructor: Hello
Создаём копию
COPY constructor: Hello
Перемещаем
MOVE constructor: Hello
После перемещения
s1: data: (null)
s3: data: Hello
Оператор присваивания перемещением
Constructor: Hello
Constructor: World
Before move assignment:
a: data: Hello
b: data: World
MOVE assignment: Hello
After move assignment:
a: data: (null)
b: data: Hello
Оператор присваивания копированием
Constructor: Original
Constructor: Target
Before copy assignment:
c: data: Original
d: data: Target
COPY assignment: Original
After copy assignment:
c: data: Original
d: data: Original
Самоприсваивание
c after self-assignment: data: Original
Copies: 2
Moves: 2
Destructor: Original
Destructor: Original
Destructor: Hello
Destructor: (null)
Destructor: Hello
Destructor: Hello
Destructor: (null)
*/