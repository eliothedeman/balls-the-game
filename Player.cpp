#include "Player.h"

namespace balls
{
Player::Player(uint8_t n)
{
    player_num = n;
    x = 5;
    switch (n)
    {
    case 1:
        y = 0;
        break;
    case 2:
        y = 120;
        break;
    }

    game_ball.isStatic = false;
}

void Player::draw(A& a)
{

    // print score
    a.setCursor(this->y, this->x);
    a.print(this->game_ball.v.x);

    switch (ballState)
    {
    case GameBall:
        game_ball.draw(a);
    case Static_2:
        static_ball_2.draw(a);
    case Static_1:
        static_ball_1.draw(a);
    case NoBalls:
        break;
    }
}
}