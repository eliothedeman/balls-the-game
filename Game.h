#pragma once

#include <Arduboy2.h>
#include "Object.h"

namespace balls
{

const int8_t BALL_RADIUS = 5;

struct Ball : Object
{
  Ball() {
    x = WIDTH / 2;
    y = HEIGHT / 2;
  }
  void draw() override;
  bool touches(Object &o) override;
  Vector v;
};

const int8_t NoBalls = 0;
const int8_t Static_1 = 1;
const int8_t Static_2 = 2;
const int8_t GameBall = 3;

struct Player : Object
{
  Player(uint8_t n);
  ~Player(){};
  void draw() override;
  bool touches(Object &o) override;

  Ball static_ball_1;
  Ball static_ball_2;
  Ball game_ball;
  int8_t player_num;
  int8_t score = 0;
  int8_t ballState = 0;
};

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
  void draw() override;
  void simulate();
  Player player1;
  Player player2;
  int8_t current_state;
};
} // namespace balls