#include "Game.h"
#include "Object.h"
#include "singletons.h"

namespace balls
{

static int placeGameBall(Player *p)
{

    // TODO: get this right you idiot
    auto offset = p->player_num - 1;
    offset = offset * WIDTH;
    if (offset > 0)
    {
        offset -= BALL_RADIUS;
    }
    p->game_ball.x = offset;

    if (A.justPressed(A_BUTTON))
    {
        return 1;
    }
    if (A.pressed(UP_BUTTON))
    {
        p->game_ball.y--;
    }
    if (A.pressed(DOWN_BUTTON))
    {
        p->game_ball.y++;
    }
    return 0;
}

static int placeBall(Player *p)
{

    Ball *b;
    switch (p->ballState)
    {
    case NoBalls:
        p->ballState = Static_1;
    case Static_1:
        b = &p->static_ball_1;
        break;
    case Static_2:
        b = &p->static_ball_2;
        break;
    case GameBall:
        return placeGameBall(p);
        break;
    default:
        A.print("ERROR");
        A.print(p->ballState);
        return 0;
    }

    if (A.justPressed(A_BUTTON))
    {
        p->ballState++;
        return 0;
    }
    if (A.pressed(UP_BUTTON))
    {
        b->y--;
    }
    if (A.pressed(DOWN_BUTTON))
    {
        b->y++;
    }
    if (A.pressed(LEFT_BUTTON))
    {
        b->x--;
    }
    if (A.pressed(RIGHT_BUTTON))
    {
        b->x++;
    }

    return 0;
}

static bool simulateFrame(Game *g)
{
    auto &p1 = g->player1;
    auto &p2 = g->player2;

    p1.game_ball.y--;
    p2.game_ball.y--;
}

void Game::simulate()
{
    int stateChange = 0;
    switch (current_state)
    {
    case GAME_START:
        stateChange += 1;
        break;
    case P1_PLACE_BALLS:
        stateChange = placeBall(&player1);
        break;
    case P2_PLACE_BALLS:
        stateChange = placeBall(&player2);
        break;
    case PLAY_GAME:
        simulateFrame(this);
    case UPDATE_SCORE:
        break;
    case DISPLAY_WINNER:
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
    current_state = 0;
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

    switch (ballState)
    {
    case GameBall:
        game_ball.draw();
    case Static_2:
        static_ball_2.draw();
    case Static_1:
        static_ball_1.draw();
    case NoBalls:
        break;
    }
}

bool Player::touches(Object &o)
{
    return false;
}

void Ball::draw()
{
    A.drawCircle(x, y, BALL_RADIUS);
}

bool Ball::touches(Object &o)
{
    return false;
}
}