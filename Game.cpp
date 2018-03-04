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

void Ball::move() {
    x += v.x;
    y += v.y;
}

static void simBalls(Ball** b) {
    for (auto i = 0; i < 6; i++) {
        for (auto j = 0; j < 6; j++) {
            if (i == j) {
                continue;
            }
            if (b[i]->touches(b[j])) {
                b[i]->v.x *= -1;
                b[i]->v.y *= -1;
            }
        }
    }

    for (auto i = 0; i < 6; i++) {
        b[i]->move();
    }
}

static void fillBallArray(Player& p1, Player& p2, Ball** b) {
    b[0] = &p1.game_ball;
    b[1] = &p1.static_ball_1;
    b[2] = &p1.static_ball_2;
    b[3] = &p2.game_ball;
    b[4] = &p2.static_ball_1;
    b[5] = &p2.static_ball_2;
}

static void simulateFrame(Game *g)
{
    static Ball* b[6];
    fillBallArray(g->player1, g->player2, b);
    simBalls(b);
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
        player1.game_ball.v.x = 1;
        break;
    case P2_PLACE_BALLS:
        stateChange = placeBall(&player2);
        player2.game_ball.v.x = -1;
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


void Ball::draw()
{
    A.drawCircle(x, y, BALL_RADIUS);
}

bool Ball::touches(const Ball* b)
{
    auto tx = abs(x - b->x);
    auto ty = abs(y - b->y);
    auto distance = tx + ty;
    return distance < BALL_DIAMETER;
}
}