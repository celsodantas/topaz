#include "Scene.hpp"
#include "engine/ShaderLoader.hpp"

Topaz::Scene::Scene()
{
  Importer::Importer imp(_3dModelPath);

  numbVertices = imp.getNumIndexes();
  matrix = glm::mat4(1.0f);

  vao = loadIntoGPU(imp);

  shaderId = ShaderLoader::LoadShaders("src/shaders/triangles.vert", "src/shaders/triangles.frag");
}

void Topaz::Scene::setShaderUniforms()
{
  int matrixLocBuffer = glGetUniformLocation(shaderId, "matrix");

  glUniformMatrix4fv(matrixLocBuffer, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Topaz::Scene::animate()
{
}
