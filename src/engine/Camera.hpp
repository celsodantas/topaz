#ifndef CAMERA_HPP
#define CAMERA_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "EventGrandCentral.hpp"

namespace Topaz {
  namespace Engine {
    class Camera : public Listener {
    public:
      Camera()
      {
        EventGrandCentral::instance().addListener(this);

        // Static location for now
        matrix = glm::lookAt(
            glm::vec3(0.f,  -2.f,   0.5f), // Camera position, in World Space
            glm::vec3(0,  0.5f, 0), // and looks at
            glm::vec3(0,  0,    1)  // Head is up (set to 0,-1,0 to look upside-down)
        );
      }

      void handleEvent(Engine::Event event)
      {
        printf("Camera moooovements: %s\n", event.type);
      }

      glm::mat4 matrix;
    };
  }
}

#endif
