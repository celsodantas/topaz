#ifndef ENGINE_HPP
#define ENGINE_HPP

// #include <SDL2/SDL.h>
#include <glfw/glfw3.h>

namespace Topaz {

  class Engine {
  public: 
    Engine() {};
    
    void initialize();
    void swapBuffer();
    void quit();

  private:
    // SDL_Renderer* _displayRenderer;
    GLFWwindow   *_window;

    int _winWidth  = 800;
    int _winHeight = 600;

    void initGL();
    void setViewport();


  };
}

#endif