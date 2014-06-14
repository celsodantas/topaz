#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "engine/Core.hpp"
#include "CommonHeader.hpp"

namespace Topaz {
  class Player : public GameObject {
  public:
    Player();
    void setShaderUniforms();
    void animate();

    std::string _3dModelPath = "assets/monkey.dae";

    glm::mat4 matrix;
  };
}

#endif
