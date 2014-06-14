#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "engine/Core.hpp"

namespace Topaz {
  using namespace std;

  class Game {
  public:
    Game(Engine::Core engine);
    void run();

  private:

    bool _running = false;

    Engine::Core _engine;
    std::vector<GameObject*> _gameObjects;
  };
}

#endif
