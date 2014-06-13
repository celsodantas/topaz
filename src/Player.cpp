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

Topaz::Player::Player(Engine engine)
{
  Importer::Importer imp(_3dModelPath);

  numbVertices = imp.getNumIndexes();
  matrix = glm::mat4(1.0f);

  vao = loadIntoGPU(imp);

  shaderId = ShaderLoader::LoadShaders("src/shaders/triangles.vert", "src/shaders/triangles.frag");
}

void Topaz::Player::setShaderUniforms()
{
  int matrixLocBuffer = glGetUniformLocation(shaderId, "matrix");

  glUniformMatrix4fv(matrixLocBuffer, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Topaz::Player::animate()
{
  float angle = 0.01f;
  matrix = matrix * glm::yawPitchRoll(0.f, 0.f, angle);
}
