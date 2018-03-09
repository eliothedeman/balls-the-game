#ifndef _H_OBJECT
#define _H_OBJECT

#include <Arduboy2.h>

namespace balls
{
using A = Arduboy2;
#define __SCALE 100
#define SCALE_DOWN(v) (v / __SCALE)
#define SCALE_UP(v) (v * __SCALE)

struct Point
{
    Point()
    {
        this->x = 0;
        this->y = 0;
    };
    Point(int16_t x, int16_t y);
    int16_t x;
    int16_t y;
};

struct Line
{
    Point start;
    Point end;
};

struct Object : Point
{
    virtual ~Object(){};
    virtual void draw(A & a);
};

struct Vector : Point
{
    Vector();
    Vector(int16_t x, int16_t y);
    Vector &operator=(const balls::Vector &v);
    Vector operator+(const Vector &r);
    Vector &operator+=(const Vector &v);
    int16_t velocity() const;
};

extern Vector V_STATIC;
extern Vector V_UP;
extern Vector V_DOWN;
extern Vector V_LEFT;
extern Vector V_RIGHT;

} // namespace hello

#endif
