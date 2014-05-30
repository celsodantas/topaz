#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>

namespace Topaz {

  class Engine {
  public: 
    Engine() {};
    
    void initialize();
    void quit();

  private:
    SDL_Renderer* _displayRenderer;

    int _winWidth  = 800;
    int _winHeight = 600;

    void initGL();
    void setViewport();


  };
}

#endif