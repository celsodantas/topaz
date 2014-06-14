#define GL_GLEXT_PROTOTYPES 1

#include "Core.hpp"
#include <iostream>
#include <unistd.h>

void Topaz::Engine::Core::initialize()
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
  object->animate();

  glUseProgram(object->shaderId);
  setShaderMVP(object->shaderId);
  object->setShaderUniforms();

  glBindVertexArray(object->vao);

  glDrawElements(GL_TRIANGLES, object->numbVertices, GL_UNSIGNED_INT, 0);
}

void Topaz::Engine::Core::setShaderMVP(uint32 shaderId)
{
  glm::mat4 perspective = glm::perspective(90.f, 4.f/3.f, 0.1f, 100.f);
  glm::mat4 mvp = perspective * camera();

  int buffer = glGetUniformLocation(shaderId, "mvp");
  glUniformMatrix4fv(buffer, 1, GL_FALSE, glm::value_ptr(mvp));
}

glm::mat4 Topaz::Engine::Core::camera()
{
  return glm::lookAt(
      glm::vec3(0.f,  -2.f,   0.5f), // Camera position, in World Space
      glm::vec3(0,  0.5f, 0), // and looks at
      glm::vec3(0,  0,    1)  // Head is up (set to 0,-1,0 to look upside-down)
  );
}
