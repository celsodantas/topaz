#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include "engine/Core.hpp"
#include "CommonHeader.hpp"

namespace Topaz {
  class Scene : public GameObject {
  public:
    Scene();
    void setShaderUniforms();
    void animate();

    std::string _3dModelPath = "assets/scene_01.dae";

    glm::mat4 matrix;
  };
}

#endif
