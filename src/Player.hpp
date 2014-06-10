#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "engine/Engine.hpp"

namespace Topaz {
  class Player {
  public:
    Player(Engine engine);

    std::string _3dModelPath = "assets/godzilla.dae";
  };
}

#endif
