#include <iostream>
#include "engine/Core.hpp"
#include "Game.hpp"

int main()
{
  Topaz::Game *game = new Topaz::Game();

  Topaz::Engine::Core engine(game);
  engine.run();
  engine.quit();

  return 0;
}
