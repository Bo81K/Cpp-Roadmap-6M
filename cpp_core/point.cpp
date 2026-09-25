#include <cmath>
#include <iostream>

class Point
{
public:
    Point();
    Point(double x, double y);

    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

    double distanceTo(const Point& other) const;
    void print() const;

private:
    double x_ = 0.0;
    double y_ = 0.0;

};

Point::Point() = default;

Point::Point(double x, double y)
{
    x_ = x;
    y_ = y;
}

double Point::x() const
{
    return x_;
}

double Point::y() const
{
    return y_;
}

void Point::setX(double x)
{
    x_ = x;
}

void Point::setY(double y)
{
    y_ = y;
}

double Point::distanceTo(const Point& other) const
{
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

void Point::print() const
{
    std::cout << "(" << x_ << "," << y_ << ")";
}

int main()
{
    Point p1;
    Point p2(3.0, 4.0);

    p1.print();
    std::cout << '\n';

    p2.print();
    std::cout << '\n';

    std::cout << "distance = " << p1.distanceTo(p2) << '\n';

    return 0;
}