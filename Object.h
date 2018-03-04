#pragma once

namespace balls {

struct Point {
    int8_t x = 0;
    int8_t y = 0;
};

struct Object : Point {
    virtual ~Object() {};
    virtual void draw() ;
};

struct Vector : Point {
};

} // namespace hello
