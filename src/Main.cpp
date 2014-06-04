#include <iostream>
#include "engine/Engine.hpp"
#include "Logger.hpp"
#include "Game.hpp"
 
int main(int argc, char *argv[])
{
  Topaz::Engine engine;
  engine.initialize();

  Topaz::Game game = Topaz::Game(engine);
  game.run();

  engine.quit();
  
  return 0;
}
