#pragma once

#include "Object.h"
#include <Arduboy2.h>

namespace balls
{

struct Ball : Object
{
  void draw() override;
  bool touches(Object &o) override;
};

struct Player : Object
{
  Player(uint8_t n);
  ~Player(){};
  void draw() override;
  bool touches(Object &o) override;

  Ball static_ball_1;
  Ball static_ball_2;
  Ball game_ball;
  uint8_t player_num;
  uint8_t score = 0;
};

enum State
{
  P1_STATIC_1 = 0,
  P1_STATIC_2 = 1,
  P1_GAME_BALL = 2,
  P2_STATIC_1 = 3,
  P2_STATIC_2 = 4,
  P2_GAME_BALL = 5,
  UPDATE_SCORE = 6,
  DISPLAY_WINNER = 7
};

struct Game : Object
{
  Game();
  ~Game(){};
  void draw() override;
  void simulate();
  Player player1;
  Player player2;
  int8_t current_state;
};
} // namespace balls