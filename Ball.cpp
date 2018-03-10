#include "Ball.h"

namespace balls
{

Ball::Ball() : v(0, 0) {

    x = WIDTH / 2;
    y = HEIGHT / 2;
    isStatic = true;
}
void Ball::move()
{
    x += v.x;
    y += v.y;
}
void Ball::draw(A &a)
{
    a.drawCircle(x, y, BALL_RADIUS);
}

int16_t Ball::distance(const Ball &b)
{
   return abs(Point::distance(b) - BALL_DIAMETER);
}

int16_t Ball::distance(const Line& l)
{

    auto s1 = (l.start.y - l.end.y) * this->x;
    auto s2 = (l.start.x - l.end.x) * this->y;
    auto s3 = l.end.x * l.start.y;
    auto s4 = l.start.x * l.end.y;

    auto s5 = abs(s1 - s2) + abs(s3 - s4);

    return abs((s5 / l.start.distance(l.end)) - BALL_RADIUS);

}
}