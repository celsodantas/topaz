#include "Engine.hpp"
#include "Logger.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>

void Topaz::Engine::initialize() 
{
  Logger::print("Initializing SDL");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* displayWindow;
  SDL_RendererInfo displayRendererInfo;
  SDL_CreateWindowAndRenderer(_winWidth, _winHeight, SDL_WINDOW_OPENGL, &displayWindow, &_displayRenderer);
  SDL_GetRendererInfo(_displayRenderer, &displayRendererInfo);

  if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED)   == 0 || 
      (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) 
  {
    std::cout << "Error on SDL initialization. Quitting game" << std::endl;
    SDL_Quit();
  }

  initGL();
}

void Topaz::Engine::quit()
{
  SDL_Quit();
}

void Topaz::Engine::initGL()
{
  /* Enable smooth shading */
  glShadeModel( GL_SMOOTH );

  /* Set the background black */
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

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
  gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

  /* Make sure we're chaning the model view and not the projection */
  glMatrixMode( GL_MODELVIEW );

  /* Reset The View */
  glLoadIdentity( );
}