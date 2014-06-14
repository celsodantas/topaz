#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "engine/Core.hpp"
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

    uint32 shaderId;
    uint32 numbVertices;
    uint32 vao;
  };
}

#endif
