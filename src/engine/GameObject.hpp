#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "engine/Engine.hpp"
#include "CommonHeader.hpp"

namespace Topaz {

  class GameObject
  {
  public:
    GameObject() {};
    ~GameObject() {};

    virtual void setShaderUniforms() { printf("virtual method\n");};

    GLuint shaderId;
    GLuint numbVertices;
    GLuint vao;
  };
}

#endif
