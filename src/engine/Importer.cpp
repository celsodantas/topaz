#include "Importer.hpp"
#include <cassert>
#include <iostream>

Topaz::Importer::Importer(std::string filePath)
{
  const aiScene* scene = _importer.ReadFile( filePath,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  if(!scene)
    std::cout << _importer.GetErrorString() << std::endl;
  else
    std::cout << "Scene \""<< filePath << "\" loaded" << std::endl;

  printf("  %i animations\n", scene->mNumAnimations);
  printf("  %i cameras\n", scene->mNumCameras);
  printf("  %i lights\n", scene->mNumLights);
  printf("  %i materials\n", scene->mNumMaterials);
  printf("  %i meshes\n", scene->mNumMeshes);
  printf("  %i textures\n", scene->mNumTextures);

  _mesh = scene->mMeshes[0];

  loadData();
  loadIndexes();
}

void Topaz::Importer::loadIndexes()
{
  _indexes.reserve(_mesh->mNumFaces);

  for (uint i = 0; i < _mesh->mNumFaces; ++i)
  {
    aiFace &face = _mesh->mFaces[i];
    assert(face.mNumIndices == 3);
    for (uint j = 0; j < face.mNumIndices; ++j)
    {
      _indexes.push_back(face.mIndices[j]);
    }
  }
}

void Topaz::Importer::loadData()
{
  _data.reserve(_mesh->mNumVertices * 2);

  for (int i=0; i < _mesh->mNumVertices; i++)
  {
    _data.push_back(_mesh->mVertices[i]);
    _data.push_back(_mesh->mNormals[i]);
  }
}

uint Topaz::Importer::getIndexesSize()
{
  return sizeof(uint) * _indexes.size();
}

void * Topaz::Importer::getIndexes()
{
  return &_indexes[0];
}

uint Topaz::Importer::getDataSize()
{
  return sizeof(aiVector3D) * _data.size();
}

void * Topaz::Importer::getData()
{
  return &_data[0];
}

uint Topaz::Importer::getNumbVertices()
{
  return _mesh->mNumVertices;
}

uint Topaz::Importer::getNumIndexes()
{
  return _mesh->mNumFaces * 3;
}

int Topaz::Importer::getVerticesStride()
{
  return sizeof(aiVector3D) * 2;
}

int Topaz::Importer::getNormalsStride()
{
  return sizeof(aiVector3D) * 2;
}

void* Topaz::Importer::getVerticesStartAt()
{
  return 0; // no shift
}

void* Topaz::Importer::getNormalsStartAt()
{
  return (void *) sizeof(aiVector3D);
}
