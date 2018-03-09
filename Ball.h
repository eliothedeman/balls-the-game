#ifndef _H_BALL
#define _H_BALL

#include "Object.h"

namespace balls
{
const int8_t BALL_RADIUS = 5;
const int8_t BALL_DIAMETER = 2 * BALL_RADIUS;

struct Ball : Object
{
  Ball();
  void draw(A&) override;
  bool touches(const Ball& b);
  void move();

  Vector v;
  bool isStatic;
};
}

#endif