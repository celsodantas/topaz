#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "engine/Engine.hpp"
#include "CommonHeader.hpp"
#include "engine/Importer.hpp"

namespace Topaz {

  class GameObject
  {
  public:
    GameObject() {};
    ~GameObject() {};

    virtual void setShaderUniforms() = 0;
    virtual void animate() = 0;

    // It returns the VAO reference
    uint loadIntoGPU(Importer importer);

    GLuint shaderId;
    GLuint numbVertices;
    GLuint vao;
  };
}

#endif
