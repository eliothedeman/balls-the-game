#include <Arduboy2.h>
#include "singletons.h"
#include "Game.h"

balls::Game game;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  balls::A.begin();
  balls::A.clear();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  balls::A.setFrameRate(60);

}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(balls::A.nextFrame())) {
    return;
  }

  balls::A.pollButtons();

  // run the simulation
  game.simulate();

  // first we clear our screen to black
  balls::A.clear();
  game.draw();
  balls::A.setCursor(WIDTH -5, HEIGHT - 10);
  balls::A.print(balls::A.cpuLoad());

  // then we finaly we tell the arduboy to display what we just wrote to the display
  balls::A.display();
}
