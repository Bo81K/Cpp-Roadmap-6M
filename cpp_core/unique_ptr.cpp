#include <iostream>
#include <memory> 

template<typename T>
class UniquePtr
{
    T *ptr;

public:
    explicit UniquePtr(T *p = nullptr) : ptr(p){}
    ~UniquePtr(){
        delete ptr;
    }
    
    // Запрет копирования
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
    
    // Разрешение перемещения
    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr){
        other.ptr = nullptr;
    }
    UniquePtr &operator=(UniquePtr &&other) noexcept {
        if(this == &other){
            return *this;
        }

        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    
    T *get() const{
        return ptr;
    }
    T &operator*() const{
        return *ptr;
    }
    T *operator->() const{
        return ptr;
    }
};

int main() {
    UniquePtr<int> p1(new int(42));
    std::cout << *p1 << '\n';                 // 42
    std::cout << p1.get() << '\n';            // адрес

    UniquePtr<int> p2 = std::move(p1);        // перемещение
    // p1 теперь пуст, p2 владеет объектом
    if (!p1.get()) std::cout << "p1 is null\n";
    std::cout << *p2 << '\n';                 // 42

    UniquePtr<int> p3;
    p3 = std::move(p2);                       // перемещающее присваивание
    // p2 пуст, p3 владеет
    std::cout << *p3 << '\n';                 // 42

    return 0;
}