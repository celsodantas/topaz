#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "engine/Engine.hpp"
#include "engine/GameObject.hpp"
#include "CommonHeader.hpp"

namespace Topaz {
  class Player : public GameObject {
  public:
    Player(Engine engine);
    void setShaderUniforms();

    std::string _3dModelPath = "assets/monkey.dae";
  };
}

#endif
