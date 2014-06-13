#include "engine/GameObject.hpp"
#include "CommonHeader.hpp"

uint32 Topaz::GameObject::loadIntoGPU(Importer imp)
{
  // VAO
  uint32 vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // EBO
  uint32 ebo = 0;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, imp.getIndexesSize(), imp.getIndexes(), GL_STATIC_DRAW);

  // VBO (uploading to GPU)
  uint32 vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, imp.getDataSize(), imp.getData(), GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, imp.getVerticesStride(), imp.getVerticesStartAt());

  // Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, imp.getNormalsStride(), imp.getNormalsStartAt());

  return vao;
}
