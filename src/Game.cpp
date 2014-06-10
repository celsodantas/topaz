#include "Game.hpp"
#include "Player.hpp"

Topaz::Game::Game(Engine engine) {

  // Load player
  Player player(engine);

  // No need to call this now
  // as the loop is inside the Player class
  //engine.swapBuffer();

}

void Topaz::Game::run() {

}
