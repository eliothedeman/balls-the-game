#include "Game.h"
#include "Object.h"
#include "singletons.h"

namespace balls
{

static int placeBall(Ball &b)
{
    A.pollButtons();

    if (A.pressed(A_BUTTON))
    {
        return 1;
    }
    if (A.pressed(UP_BUTTON))
    {
        b.y--;
    }
    if (A.pressed(DOWN_BUTTON))
    {
        b.y++;
    }
    if (A.pressed(LEFT_BUTTON))
    {
        b.x--;
    }
    if (A.pressed(RIGHT_BUTTON))
    {
        b.x++;
    }

    return 0;
}

void Game::simulate()
{
    int stateChange = 0;
    switch (current_state)
    {
    case State::P1_STATIC_1:
        stateChange = placeBall(player1.static_ball_1);
        break;
    case State::P1_STATIC_2:
        stateChange = placeBall(player1.static_ball_2);
        break;
    case State::P1_GAME_BALL:
        stateChange = placeBall(player1.game_ball);
        break;
    case State::P2_STATIC_1:
        stateChange = placeBall(player2.static_ball_1);
        break;
    case State::P2_STATIC_2:
        stateChange = placeBall(player2.static_ball_2);
        break;
    case State::P2_GAME_BALL:
        stateChange = placeBall(player2.game_ball);
    case State::UPDATE_SCORE:
        break;
    case State::DISPLAY_WINNER:
        break;
    }

    current_state += stateChange;
}
void Game::draw()
{
    player1.draw();
    player2.draw();
}

Game::Game() : player1(1), player2(2)
{
    current_state = State::P1_STATIC_1;
}

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
}

void Player::draw()
{

    // print score
    A.setCursor(y, x);
    A.print(score);

    // draw balls this player owns
    static_ball_1.draw();
    static_ball_2.draw();
    game_ball.draw();
}

bool Player::touches(Object &o)
{
    return false;
}

void Ball::draw()
{
    A.drawCircle(x, y, 5);
}

bool Ball::touches(Object &o)
{
    return false;
}
}