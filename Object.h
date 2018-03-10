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
    
    int16_t distance(const Point& p);
    int16_t x;
    int16_t y;
};

struct Line
{

    Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
        this->start.x = x1;
        this->start.y = y1;

        this->end.x = x2;
        this->end.y = y2;
    }
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
    Vector &operator*=(const Vector &v);
    int16_t velocity() const;
};

extern Vector V_STATIC;
extern Vector V_UP;
extern Vector V_DOWN;
extern Vector V_LEFT;
extern Vector V_RIGHT;
extern Vector V_FLIP_H;
extern Vector V_FLIP_V;

extern Line L_TOP;
extern Line L_BOTTOM;
extern Line L_LEFT;
extern Line L_RIGHT;

} // namespace hello

#endif
