#include <iostream>
#include "engine/Engine.hpp"
#include "Game.hpp"

int main()
{
  Topaz::Engine engine;
  engine.initialize();

  Topaz::Game game = Topaz::Game(engine);
  // game.run();

  engine.quit();

  return 0;
}
