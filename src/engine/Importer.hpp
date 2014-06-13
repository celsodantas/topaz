#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace Topaz
{

  class Importer
  {
  public:
    Importer(std::string filePath);
    ~Importer() {};

    uint getIndexesSize();
    uint getDataSize();

    void * getIndexes();
    void * getData();

    uint getNumbVertices();
    uint getNumIndexes();

    int getVerticesStride();
    int getNormalsStride();

    void* getVerticesStartAt();
    void* getNormalsStartAt();

  private:
    Assimp::Importer _importer;
    aiMesh* _mesh;

    void loadData();
    void loadIndexes();

    std::vector<int> _indexes;
    std::vector<aiVector3D> _data;
  };
}

#endif
