#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <GLKit/GLKMath.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "engine/Engine.hpp"
#include "Logger.hpp"
#include "Game.hpp"
 
int main(int argc, char *argv[])
{
  Topaz::Engine engine;
  engine.initialize();

  Topaz::Game game = Topaz::Game(engine);
  game.run();

  engine.quit();
  
  return 0;
}
