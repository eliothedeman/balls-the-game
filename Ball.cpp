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
    if (isStatic) {
        return;
    }
    x += v.x;
    y += v.y;
}
void Ball::draw(A &a)
{
    a.drawCircle(SCALE_DOWN(x), SCALE_DOWN(y), BALL_RADIUS);
}

bool Ball::touches(const Ball &b)
{
    auto tx = abs(x - b.x);
    auto ty = abs(y - b.y);
    auto distance = tx + ty;
    return distance < BALL_DIAMETER;
}
}