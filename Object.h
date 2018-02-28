#pragma once
#include <Arduboy2.h>
namespace balls {

struct Point {
    int8_t x = 0;
    int8_t y = 0;
};

struct Object : Point {
    virtual ~Object() {};
    virtual void draw(Arduboy2& ard) ;
    virtual bool touches(Object& o) ;
};

struct Vector : Point {
};

} // namespace hello
