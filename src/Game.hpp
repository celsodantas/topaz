#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "engine/Engine.hpp"

namespace Topaz {
  using namespace std;

  class Game {
  public:
    Game(Engine engine);
    void run();

  private:

    Engine _engine;
    std::vector<GameObject*> _gameObjects;
  };
}

#endif
