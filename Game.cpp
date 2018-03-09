#include "Game.h"
#include "Object.h"

namespace balls
{

static int placeGameBall(A &a, Player &p)
{

    // TODO: get this right you idiot
    auto offset = p.player_num - 1;
    offset = offset * WIDTH;
    if (offset > 0)
    {
        offset -= BALL_RADIUS;
    }

    p.game_ball.x = SCALE_UP(offset);
    p.game_ball.v = V_STATIC;

    if (a.justPressed(A_BUTTON))
    {
        p.game_ball.v = V_STATIC;
        return 1;
    }
    if (a.pressed(UP_BUTTON))
    {
        p.game_ball.v = V_UP;
    }
    if (a.pressed(DOWN_BUTTON))
    {
        p.game_ball.v = V_DOWN;
    }
    return 0;
}

static int placeBall(A &a, Player &p)
{

    Ball *b;
    switch (p.ballState)
    {
    case NoBalls:
        p.ballState = Static_1;
    case Static_1:
        b = &p.static_ball_1;
        break;
    case Static_2:
        b = &p.static_ball_2;
        break;
    case GameBall:
        return placeGameBall(a, p);
        break;
    default:
        a.print("ERROR");
        a.print(p.ballState);
        return 0;
    }

    auto v = V_STATIC;
    if (a.justPressed(A_BUTTON))
    {
        b->v = v;
        p.ballState++;
        return 0;
    }
    if (a.pressed(UP_BUTTON))
    {
        v = V_UP;
    }
    if (a.pressed(DOWN_BUTTON))
    {
        v = V_DOWN;
    }
    if (a.pressed(LEFT_BUTTON))
    {
        v = V_LEFT;
    }
    if (a.pressed(RIGHT_BUTTON))
    {
        v = V_RIGHT;
    }
    b->v = v;

    return 0;
}

static void simBalls(Ball **b)
{
    for (auto i = 0; i < 6; i++)
    {
        for (auto j = 0; j < 6; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (b[i]->touches(*b[j]))
            {
                b[i]->v.x *= -1;
                b[i]->v.y *= -1;
            }
        }
    }

}

static void fillBallArray(Player &p1, Player &p2, Ball **b)
{
    b[0] = &p1.game_ball;
    b[1] = &p1.static_ball_1;
    b[2] = &p1.static_ball_2;
    b[3] = &p2.game_ball;
    b[4] = &p2.static_ball_1;
    b[5] = &p2.static_ball_2;
}

void Game::simulate()
{
    static Ball *b[6];
    fillBallArray(player1, player2, b);

    if (current_state == PLAY_GAME) {
        simBalls(b);
    }

    for (auto i = 0; i < 6; i++)
    {
        b[i]->move();
    }
}

void Game::input(A &a)
{
    int stateChange = 0;
    switch (current_state)
    {
    case GAME_START:
        stateChange += 1;
        break;
    case P1_PLACE_BALLS:
        stateChange = placeBall(a, player1);
        player1.game_ball.v = V_RIGHT;
        break;
    case P2_PLACE_BALLS:
        stateChange = placeBall(a, player2);
        player2.game_ball.v = V_LEFT;
        break;
    }

    current_state += stateChange;
}

void Game::draw(A &a)
{
    player1.draw(a);
    player2.draw(a);
}

Game::Game() : player1(1), player2(2)
{
    current_state = 0;
}
}