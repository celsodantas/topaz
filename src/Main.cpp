#include <iostream>
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h> 

int main() 
{
  std::string pFile = "/Users/celsodantas/code/cpp/topaz/monkey.dae";
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( pFile, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  // If the import failed, report it
  if(!scene)
  {
    std::cout << importer.GetErrorString() << std::endl;
    return false;
  } else {
    std::cout << "Scene loaded" << std::endl;
  }

  aiMesh* mesh = scene->mMeshes[0];
  int iMeshFaces = mesh->mNumFaces;

  std::cout << iMeshFaces << std::endl;
}
