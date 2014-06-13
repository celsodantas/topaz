#ifndef ENGINE_HPP
#define ENGINE_HPP

#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "engine/GameObject.hpp"
#include "CommonHeader.hpp"

namespace Topaz {

  class GameObject;

  class Engine {
  public:
    Engine() {};

    void initialize();
    void prepareNewRender();
    void swapBuffer();
    void quit();

    void draw(GameObject *object);

    void setShaderMVP(uint32 shaderId);
    glm::mat4 camera();

    GLFWwindow   *_window;

  private:

    int _winWidth  = 800;
    int _winHeight = 600;

    void initGL();
  };
}

#endif
