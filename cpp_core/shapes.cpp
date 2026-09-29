#include <iostream>
#include <cmath>

class Shape {
public:
    Shape();
    virtual ~Shape();

    virtual double area() const = 0;
    virtual void print() const = 0;

    // protected:
    // поля protected доступны классу и его наследникам
    // но не доступны снаружи
    // double area_ = 0.0;
    // в данном примере area_ не используется
};

Shape::Shape()
{
    std::cout << "Shape constructor\n";
}

Shape::~Shape()
{
    std::cout << "Shape destructor\n";
}

class Rectangle : public Shape
{
public:
    Rectangle(double width, double height);
    ~Rectangle() override;

    // переопределяем методы
    double area() const override;
    void print() const override;

private:
    double width_;
    double height_;
};

Rectangle::Rectangle(double width, double height)
{
    std::cout << "Rectangle constructor\n";
    width_ = width;
    height_ = height;
    // тут у нас доступен area_ так как Rectangle унаследован от Shape
    // area_ = width_ * height_;
}

Rectangle::~Rectangle()
{
    std::cout << "Rectangle destructor\n";
}

double Rectangle::area() const
{
    return width_ * height_;
}

void Rectangle::print() const
{
    std::cout << "Rectangle " << width_ << "x" << height_ << " with area:"
              << area() << "\n";
}

// Наследник 2
class Circle : public Shape
{
private:
    double radius_;

public:
    Circle(double radius) : radius_(radius)
    {
        std::cout << "Circle constructor\n";
    }
    ~Circle() override { std::cout << "Circle destructor\n"; }

    double area() const override { return 3.14159 * radius_ * radius_; }
    void print() const override { std::cout << "Circle radius = " << radius_ << "\n"; }
};

int main()
{
    // попытка создания экземпляра абстрактного класса
    // Shape s; error: cannot declare variable ‘s’ to be of abstract type ‘Shape’

    // массив указателей на БАЗОВЫЙ класс
    Shape *shapes[2];

    shapes[0] = new Rectangle(5.0, 3.0);
    shapes[1] = new Circle(2.0);

    std::cout << "\n Processing Shapes \n";
    for (int i = 0; i < 2; ++i)
    {
        // хотя указатель имеет тип Shape,
        // вызывается правильный метод (Rectangle или Circle)
        shapes[i]->print();
        std::cout << "Area: " << shapes[i]->area() << "\n";
    }

    std::cout << "\n Cleanup \n";
    for (int i = 0; i < 2; ++i)
    {
        delete shapes[i];
    }

    return 0;
}

/* Вывод из консоли

Shape constructor
Rectangle constructor
Shape constructor
Circle constructor

 Processing Shapes
Rectangle 5x3 with area:15
Area: 15
Circle radius = 2
Area: 12.5664

 Cleanup
Rectangle destructor
Shape destructor
Circle destructor
Shape destructor


Конструктор у нас идёт в прямом порядке, от базовой часи к наследнику
Деструктор идёт в обратном порядке уничтожая сначала наследника, а потом базовую часть
*/