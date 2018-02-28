#include "Game.h"
#include "Object.h"
#include <Arduboy2.h>

namespace balls {
    using A = Arduboy2;

    int placeBall(Arduboy2* a, Ball* b) {
        a->pollButtons();

        if (a->pressed(A_BUTTON)) {
            return 1;
        }
        if (a->pressed(UP_BUTTON)) {
            b->y--;
        }
        if (a->pressed(DOWN_BUTTON)) {
            b->y++;
        } 
        if (a->pressed(LEFT_BUTTON)) {
            b->x--;
        }
        if (a->pressed(RIGHT_BUTTON)) {
            b->x++;
        }

        return 0;
    }

    void Game::simulate() {
        int stateChange = 0;
        Ball* ballToBePlaced;
        switch (current_state) {
            case State::P1_STATIC_1:
            placeBall(player1.static_ball_1);
            break;
            case State::P1_STATIC_2:
            current_state += placeBall(player1.static_ball_2);
            break;
            case State::P1_GAME_BALL:
            current_state += placeBall(player1.game_ball);
            break;
            case State::P2_STATIC_1:
            current_state += placeBall(player2.static_ball_1);
            break;
            case State::P2_STATIC_2:
            current_state += placeBall(player2.static_ball_2);
            break;
            case State::P2_GAME_BALL:
            current_state += placeBall(player2.game_ball);
            break;
            case State::UPDATE_SCORE:
            case State::DISPLAY_WINNER:
            break;
        }
    }
    void Game::draw(Arduboy2 &a) {
        player1.draw(a);
        player2.draw(a);
    }

    Game::Game() : player1(1), player2(2){
        current_state = State::P1_STATIC_1;
    }

    Player::Player(uint8_t n) {
        player_num = n;
        x = 5;
        switch (n) {
            case 1:
            y = 0;
            break;
            case 2:
            y = 120;
            break;
        }
    }

    void Player::draw(Arduboy2& a)  {

        // print score
        a.setCursor(y, x);
        a.print(score);

        // draw balls this player owns
        static_ball_1.draw(a);
        static_ball_2.draw(a);
        game_ball.draw(a);
    }

    bool Player::touches(Object& o)  {
        return false;
    }

    void Ball::draw(Arduboy2& a)  {
        a.drawCircle(x, y, 5);
    }

    bool Ball::touches(Object& o)  {
        return false;
    }

}