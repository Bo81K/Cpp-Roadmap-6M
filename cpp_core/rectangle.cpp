#include <iostream>

// Класс Point (для автономной компиляции этого файла)
class Point {
public:
    Point() = default;
    Point(double x, double y) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void print() const { std::cout << "(" << x_ << ", " << y_ << ")"; }

private:
    double x_ = 0.0;
    double y_ = 0.0;
};

// Класс Rectangle
class Rectangle {
public:
    Rectangle(Point topLeft, double width, double height);

    double area() const;
    double perimeter() const;
    void print () const;

private:
    Point topLeft_; // Композиция: Rectangle "имеет" Point
    double width_;
    double height_;
};

Rectangle::Rectangle(Point topLeft, double width, double height)
{
    topLeft_ = topLeft;
    width_ = width;
    height_ = height;
}

double Rectangle::area() const
{
    return width_ * height_;
}

double Rectangle::perimeter() const
{
    return (width_ + height_) * 2;
}

void Rectangle::print() const
{
    std::cout << "Rectagle at " ;
    topLeft_.print();
    std::cout << ", " << "width: " << width_ << " height: " << height_;
}

int main() 
{
    Point corner(2.0, 3.0);
    Rectangle rect(corner, 5.0, 10.0);

    std::cout << "Testing Rectangle:\n";
    rect.print();
    std::cout << "\nArea: " << rect.area() << "\n";
    std::cout << "Perimeter: " << rect.perimeter() << "\n";

    return 0;
}