#include <iostream>
#include "engine/Core.hpp"
#include "Game.hpp"

int main()
{
  Topaz::Engine::Core engine;
  engine.initialize();

  Topaz::Game game = Topaz::Game(engine);
  game.run();

  engine.quit();

  return 0;
}
