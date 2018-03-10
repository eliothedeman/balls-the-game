#include "Object.h"

namespace balls
{


void Object::draw(A &a)
{
}

Point::Point(int16_t x, int16_t y)
{
    this->x = x;
    this->y = y;
}

Vector::Vector() : Vector(0, 0)
{
}

Vector::Vector(int16_t x, int16_t y) : Point(x,y) {
}

Vector &Vector::operator=(const Vector &v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector Vector::operator+(const Vector &r)
{
    return Vector(this->x + r.x, this->y + r.y);
}

Vector &Vector::operator+=(const Vector &v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector V_STATIC(0, 0);
Vector V_UP(0, -1);
Vector V_DOWN(0, 1);
Vector V_LEFT(-1, 0);
Vector V_RIGHT(1, 0);
}