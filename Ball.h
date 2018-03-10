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
  int16_t distance(const Ball& b);
  int16_t distance(const Line& l);
  void move();

  Vector v;
  bool isStatic;
};
}

#endif