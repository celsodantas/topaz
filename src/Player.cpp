#include "Player.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>
#include "engine/ShaderLoader.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "engine/Engine.hpp"
#include "engine/Importer.hpp"

typedef unsigned char BYTE;

Topaz::Player::Player(Engine engine)
{
  Importer::Importer imp(_3dModelPath);

  numbVertices = imp.getNumIndexes();

  // VAO
  // Vertex Array Object
  vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // EBO
  // Element Buffer Object
  GLuint ebo = 0;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, imp.getIndexesSize(), imp.getIndexes(), GL_STATIC_DRAW);

  // VBO (uploading to GPU)
  GLuint vbo = 0;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, imp.getDataSize(), imp.getData(), GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D)*2, 0);

  // Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D)*2, (void *) sizeof(aiVector3D));

  shaderId = ShaderLoader::LoadShaders("src/shaders/triangles.vert", "src/shaders/triangles.frag");

  while (!glfwWindowShouldClose(engine._window))
  {
    engine.draw(this);
    engine.swapBuffer();

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (engine._window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(engine._window, 1);
  }

}

void Topaz::Player::setShaderUniforms()
{
  glm::mat4 matrix(1.f);

  static float angle = 0;
  angle += 0.01;
  matrix = matrix * glm::yawPitchRoll(0.f, 0.f, angle);

  int matrixLocBuffer = glGetUniformLocation(shaderId, "matrix");

  glUniformMatrix4fv(matrixLocBuffer, 1, GL_FALSE, glm::value_ptr(matrix));

}
