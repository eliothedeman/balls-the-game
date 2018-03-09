#ifndef _H_PLAYER
#define _H_PLAYER

#include "Object.h"
#include "Ball.h"

namespace balls
{
const int8_t NoBalls = 0;
const int8_t Static_1 = 1;
const int8_t Static_2 = 2;
const int8_t GameBall = 3;

struct Player : Object
{
    Player(uint8_t n);
    ~Player(){};
    void draw(A&) override;

    Ball static_ball_1;
    Ball static_ball_2;
    Ball game_ball;
    int8_t player_num;
    int8_t score = 0;
    int8_t ballState = 0;
};
}

#endif