#ifndef ENGINE_HPP
#define ENGINE_HPP

#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>

namespace Topaz {

  class Engine {
  public:
    Engine() {};

    void initialize();
    void swapBuffer();
    void quit();
    GLFWwindow   *_window;

  private:

    int _winWidth  = 800;
    int _winHeight = 600;

    void initGL();
  };
}

#endif
