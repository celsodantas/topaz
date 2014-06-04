#define GL_GLEXT_PROTOTYPES 1

#include "Engine.hpp"
#include "../Logger.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>
#include <glfw/glfw3.h>
#include <OpenGL/glu.h>

#include <unistd.h>

void Topaz::Engine::initialize() 
{
  // if ( glfwInit() < 0 ) 
  // {
  //     std::cout << "Error initializing glfwInit() in " << __FILE__ << ":" << __LINE__ << std::endl;
  //     exit( EXIT_FAILURE );
  // }

  // glfwWindowHint(GLFW_SAMPLES, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  // if ( !(_window = glfwCreateWindow(800, 600, "Title", 0, 0)) ) 
  // {
  //     // closeWindow();
  //     glfwTerminate();
  //     std::cout << "Error opening windows glfwCreateWindow() in " << __FILE__ << ":" << __LINE__ << std::endl;
  //     exit( EXIT_FAILURE );
  // }
    
  // glfwMakeContextCurrent(_window);

  

  // Logger::print("Initializing SDL");

  // if (SDL_Init(SDL_INIT_VIDEO) < 0)
  // {
  //   std::cout << "Error on SDL initialization. Quiting game" << std::endl;
  //   printf("SDL_Init failed: %s\n", SDL_GetError());
  // }

  // // Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
  // _displayWindow = SDL_CreateWindow("SDL2/OpenGL Demo", 0, 0, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  
  // // Create an OpenGL context associated with the window.
  // if (!SDL_GL_CreateContext(_displayWindow))
  // {
  //   std::cout << "Error on OpenGL context" << std::endl;  
  // }
  
  // // SDL_RendererInfo displayRendererInfo;
  // // SDL_CreateWindowAndRenderer(_winWidth, _winHeight, SDL_WINDOW_OPENGL, &displayWindow, &_displayRenderer);
  // // SDL_GetRendererInfo(_displayRenderer, &displayRendererInfo);

  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); 
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // SDL_GLContext context = SDL_GL_CreateContext(0);

  // // if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED)   == 0 || 
  // //     (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) 
  // // {
  // //   std::cout << "Error on SDL initialization. Quiting game" << std::endl;
  // //   SDL_Quit();
  // // }

  // std::cout << glGetString(GL_VERSION) << std::endl;

  // initGL();
  // setViewport();
}

void Topaz::Engine::quit()
{
  // SDL_Quit();
}

void Topaz::Engine::initGL()
{
  /* Enable smooth shading */
  glShadeModel( GL_SMOOTH );

  /* Set the background black */
  glClearColor( 1.0f, 0.5f, 0.0f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT );

  /* Depth buffer setup */
  glClearDepth( 1.0f );

  /* Enables Depth Testing */
  glEnable( GL_DEPTH_TEST );

  /* The Type Of Depth Test To Do */
  glDepthFunc( GL_LEQUAL );

  /* Really Nice Perspective Calculations */
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Topaz::Engine::setViewport()
{
  /* Height / width ration */
  GLfloat ratio;

  /* Protect against a divide by zero */
  if ( _winHeight == 0 ) 
  {
    _winHeight = 1;
  }

  ratio = ( GLfloat ) _winWidth / ( GLfloat ) _winHeight;

  /* Setup our viewport. */
  glViewport( 0, 0, ( GLsizei ) _winWidth, ( GLsizei ) _winHeight );

  /* change to the projection matrix and set our viewing volume. */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );

  /* Set our perspective */
  // gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

  /* Make sure we're chaning the model view and not the projection */
  glMatrixMode( GL_MODELVIEW );

  /* Reset The View */
  glLoadIdentity( );

}

void Topaz::Engine::swapBuffer()
{
  glfwSwapBuffers(_window);
  usleep(2000000);

  // SDL_RenderPresent(_displayRenderer);
}