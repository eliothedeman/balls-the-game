#ifndef _H_GAME
#define _H_GAME
#include <Arduboy2.h>
#include "Object.h"
#include "Player.h"
#include "Ball.h"

namespace balls
{

const int8_t GAME_START = 0;
const int8_t P1_PLACE_BALLS = 1;
const int8_t P2_PLACE_BALLS = 2;
const int8_t PLAY_GAME = 3;
const int8_t UPDATE_SCORE = 4;
const int8_t DISPLAY_WINNER = 5;

struct Game : Object
{
  Game();
  ~Game(){};
  void input(A&);
  void simulate();
  void draw(A&) override;
  Player player1;
  Player player2;
  int8_t current_state;
};
} // namespace balls

#endif