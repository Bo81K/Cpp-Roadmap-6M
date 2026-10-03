#include <iostream>
#include <vector>
#include <stdexcept> // для runtime_error

template <typename T>
class Stack {
private:
    std::vector<T> data_; 

public:
    void push (const T& value){
        data_.push_back(value);
    }

    void pop(){
        if(data_.size() == 0){
            throw std::runtime_error("Stack is empty");
        }

        data_.pop_back();
    }

    T top() const {
        if(data_.size() == 0){
            std::runtime_error("Stack is empty");
        }

        return data_.back();
    }

    bool isEmpty () const {
        return data_.size() == 0; // или data_.empty();
    }

    size_t size() const {
        return data_.size();
    }
};

int main() {
    std::cout << "Стек целых чисел\n";
    Stack<int> intStack;
    
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    std::cout << "Top: " << intStack.top() << "\n";
    std::cout << "Size: " << intStack.size() << "\n";
    
    intStack.pop();
    std::cout << "After pop, top: " << intStack.top() << "\n";

    std::cout << "\nCтек строк\n";
    Stack<std::string> stringStack;
    
    stringStack.push("Hello");
    stringStack.push("World");
    
    std::cout << "Top: " << stringStack.top() << "\n";
    
    stringStack.pop();
    std::cout << "After pop, top: " << stringStack.top() << "\n";

    std::cout << "\nТест пустого стека\n";
    Stack<int> emptyStack;
    
    try {
        emptyStack.top();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}