#include <iostream>
#include <cmath>

class Shape {
public:
    Shape();
    ~Shape();

    double area() const;
    void print () const;

protected:
    // поля protected доступны классу и его наследникам
    // но не доступны снаружи
    // double area_ = 0.0;
    // в данном примере area_ не используется
};

Shape::Shape() {
    std::cout << "Shape constructor\n";
}

Shape::~Shape() {
    std::cout << "Shape destructor\n";
}

double Shape::area() const {
    return 0.0;
}

void Shape::print() const {
    std::cout << "Unknown shape\n";
}

class Rectangle : public Shape {
public:
    Rectangle(double width, double height);
    ~Rectangle();

    // переопределяем методы
    double area() const;
    void print() const;

private:
    double width_;
    double height_;
};



Rectangle::Rectangle(double width, double height) {
    std::cout << "Rectangle constructor\n";
    width_ = width;
    height_ = height;
    // тут у нас доступен area_ так как Rectangle унаследован от Shape
    // area_ = width_ * height_;
}

Rectangle::~Rectangle(){
    std::cout << "Rectangle destructor\n";
}

double Rectangle::area() const{
    return width_ * height_;
}

void Rectangle::print() const {
    std::cout << "Rectangle " << width_ << "x" << height_ << " with area:"
                << area() << "\n";
}

int main(){
    // Shape s;
    // s.print();

    Rectangle rect (5.0, 3.0);
    rect.print();
    std::cout << "Area: " << rect.area() << "\n";
    return 0;
}

/* Вывод из консоли

Shape constructor
Rectangle constructor
Rectangle 5x3 with area:15
Area: 15
Rectangle destructor
Shape destructor

Конструктор у нас идёт в прямом порядке, от базовой часи к наследнику
Деструктор идёт в обратном порядке уничтожая сначала наследника, а потом базовую часть
*/