#ifndef CORE_HPP
#define CORE_HPP

#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonHeader.hpp"
#include "engine/GameObject.hpp"
#include "engine/Camera.hpp"

namespace Topaz {
  class GameObject;

  namespace Engine {

    struct Cursor {
      double x, y, deltaX, deltaY;
    };

    class Core {
    public:
      Core() {};

      void initialize();
      void prepareNewRender();
      void swapBuffer();
      void quit();

      void draw(GameObject *object);

      void setShaderMVP(uint32 shaderId);

      Cursor cursor;
      void updateCursorData();

      GLFWwindow   *_window;
      Camera       camera;

    private:

      int _winWidth  = 800;
      int _winHeight = 600;

      void initGL();
    };
  }
}

#endif
