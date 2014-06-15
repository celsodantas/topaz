#ifndef CAMERA_HPP
#define CAMERA_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

// #include "Core.hpp"

namespace Topaz {
  namespace Engine {
    class Core;

    class Camera  {
    public:
      Camera();
      void tick(Engine::Core engine);

      glm::mat4 matrix;
    };
  }
}

#endif
