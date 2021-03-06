#include "Player.hpp"

#include "engine/ShaderLoader.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>


Topaz::Player::Player()
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
