#include <Arduboy2.h>
#include "Game.h"

balls::Game game;
balls::A boi;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup()
{
  // initiate arduboy instance
  boi.begin();
  boi.clear();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  boi.setFrameRate(60);
}

// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop()
{
  // pause render until it's time for the next frame
  if (!(boi.nextFrame()))
  {
    return;
  }

  boi.pollButtons();
  game.input(boi);

  // run the simulation
  game.simulate();

  // first we clear our screen to black
  boi.clear();
  game.draw(boi);
  boi.setCursor(WIDTH - 5, HEIGHT - 10);
  boi.print(boi.cpuLoad());

  boi.setCursor(WIDTH - 50, HEIGHT - 10);
  boi.print(game.current_state);

  // then we finaly we tell the arduboy to display what we just wrote to the display
  boi.display();
}
