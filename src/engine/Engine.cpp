#define GL_GLEXT_PROTOTYPES 1

#include "Engine.hpp"
#include <iostream>
#include <unistd.h>

void Topaz::Engine::initialize()
{
    if ( glfwInit() < 0 )
  {
      std::cout << "Error initializing glfwInit() in " << __FILE__ << ":" << __LINE__ << std::endl;
      exit( EXIT_FAILURE );
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if ( !(_window = glfwCreateWindow(800, 600, "Title", 0, 0)) )
  {
      glfwTerminate();
      std::cout << "Error opening windows glfwCreateWindow() in " << __FILE__ << ":" << __LINE__ << std::endl;
      exit( EXIT_FAILURE );
  }

  glfwMakeContextCurrent(_window);

  initGL();
}

void Topaz::Engine::quit()
{
  glfwTerminate();
}

void Topaz::Engine::initGL()
{
  glEnable( GL_DEPTH_TEST );
  glClearDepth( 1.0f );
  glDepthFunc( GL_LEQUAL );
}

void Topaz::Engine::swapBuffer()
{
  glfwSwapBuffers(_window);
}
