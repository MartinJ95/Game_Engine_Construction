#include "vector2.hpp"

vector2::vector2() : x(0), y(0)
{
    //std::cout << "default constructor called, the value of x is " << x << " and y is " << y << std::endl;
}

vector2::vector2(float x, float y) : x(x), y(y)
{
    //std::cout << "default constructor called, the value of x is " << x << " and y is " << y << std::endl;
}

vector2::vector2(const vector2& other)
{
    //std::cout << "copy constructor. the value of x is " << other.x << " and y is " << other.y << std::endl;
    vector2::x = other.x;
    vector2::y = other.y;
}

vector2::~vector2()
{
    //std::cout << "destructor called the value of x is " << x << " and y is " << y << std::endl;
}

float vector2::getX() const
{
    return x;
}

float vector2::getY() const
{
    return y;
}

void vector2::setX(const float x)
{
    vector2::x = x;
}

void vector2::setY(const float y)
{
    vector2::y = y;
}

float vector2::length()
{
    float len = sqrt(x*x + y*y);
    return len;
}

vector2 vector2::normalise()
{
    vector2 vector;
    float len = length();
    if (len != 0)
    {
        vector.x = x/len;
        vector.y = y/len;
    }

    return vector;
}

void vector2::normaliseInPlace()
{
    float len = length();
    if (len == 0)
        return;
    x/=len;
    y/=len;
}

std::ostream& operator<<(std::ostream& os, const vector2& v)
{
    os << "x = " << v.x << std::endl;
    os << "y = " << v.y << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, vector2& v)
{
    std::cout << "enter x: ";
    is >> v.x;
    std::cout << "enter y: ";
    is >> v.y;

    return is;
}

