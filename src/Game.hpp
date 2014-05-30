#ifndef GAME_HPP
#define GAME_HPP

#include "engine/Engine.hpp"

namespace Topaz {
  class Game {
  public:
    Game(Engine engine);
    void run();
  };
}

#endif GAME_HPP