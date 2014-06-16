#define GL_GLEXT_PROTOTYPES 1

#include "Core.hpp"
#include "Game.hpp"
#include <iostream>
#include <unistd.h>

Topaz::Engine::Core::Core(Game *game) : _game(game)
{
  initWindow();
  initGL();

  game->init(*this);
}

void Topaz::Engine::Core::initWindow()
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
}

void Topaz::Engine::Core::quit()
{
  glfwTerminate();
}

void Topaz::Engine::Core::initGL()
{
  glEnable( GL_DEPTH_TEST );
  glClearDepth( 1.0f );
  glDepthFunc( GL_LEQUAL );
}

void Topaz::Engine::Core::prepareNewRender()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Topaz::Engine::Core::swapBuffer()
{
  glfwSwapBuffers(_window);
}

void Topaz::Engine::Core::draw(GameObject *object)
{
  glUseProgram(object->shaderId);
  setShaderMVP(object->shaderId);
  object->setShaderUniforms();

  glBindVertexArray(object->vao);

  glDrawElements(GL_TRIANGLES, object->numbVertices, GL_UNSIGNED_INT, 0);
}

void Topaz::Engine::Core::setShaderMVP(uint32 shaderId)
{
  glm::mat4 perspective = glm::perspective(90.f, 4.f/3.f, 0.1f, 100.f);
  glm::mat4 mvp = perspective * camera.matrix;

  int buffer = glGetUniformLocation(shaderId, "mvp");
  glUniformMatrix4fv(buffer, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Topaz::Engine::Core::updateDeltaData()
{
  static float previous_seconds = glfwGetTime ();
  float current_seconds = glfwGetTime ();
  float elapsed_seconds = current_seconds - previous_seconds;
  previous_seconds = current_seconds;

  deltaTime = elapsed_seconds;
}

void Topaz::Engine::Core::updateCursorData()
{
  static double newX, newY;
  static double oldX = 0, oldY = 0;
  glfwGetCursorPos(_window, &newX, &newY);

  double  deltaX, deltaY;

  cursor.x = newX;
  cursor.y = newY;
  cursor.deltaX = newX - oldX;
  cursor.deltaY = newY - oldY;

  oldX = newX;
  oldY = newY;

  cursor.btn1Pressed = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1);
  cursor.btn2Pressed = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_2);
}

void Topaz::Engine::Core::addGameObject(GameObject *object)
{
  assert(object != NULL);
  printf("[CORE] Adding game object\n");

  _gameObjects.push_back(object);

  printf("%lu\n", _gameObjects.size());
}

void Topaz::Engine::Core::run()
{
  _running = true;
  printf("Starting loop:\n");
  printf("Game objects: %lu\n", _gameObjects.size());

  while (_running)
  {
    updateCursorData();
    updateDeltaData();
    prepareNewRender();

    camera.tick(*this);
    _game->tick(*this);


    for (int i = 0; i < _gameObjects.size(); i++)
    {
      auto object = _gameObjects[i];
      object->animate();
      draw(object);
    }

    swapBuffer();

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (_window, GLFW_KEY_ESCAPE))
      _running = false;
  }

  glfwSetWindowShouldClose(_window, 1);
}
