#include <vector>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
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
// #include <glm/gtx/euler_angles.hpp>

#include <unistd.h>

#include "engine/Engine.hpp"

typedef unsigned char BYTE;
using namespace std;
#define PI 3.141592653589793238462f

Topaz::Player::Player(Engine engine)
{
  // Importer::Importer importer("monkey.dae");

  // auto indexes = importer.getIndexes();
  // auto vertexes = importer.getVertexes();

  //////////////////////////////////
  // Assimp = Collada importer

  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( _3dModelPath,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  if(!scene)
  {
    printf(importer.GetErrorString());
  }
  else
  {
    printf("Scene loaded");
  }

  printf("  %i animations\n", scene->mNumAnimations);
  printf("  %i cameras\n", scene->mNumCameras);
  printf("  %i lights\n", scene->mNumLights);
  printf("  %i materials\n", scene->mNumMaterials);
  printf("  %i meshes\n", scene->mNumMeshes);
  printf("  %i textures\n", scene->mNumTextures);

  aiMesh* mesh = scene->mMeshes[0];

  std::vector<aiVector3D> data;

  int indexCount = 0;

  // VAO
  // Vertex Array Object
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // EBO
  // Element Buffer Object
  {
    // Organizing element faces indexes into a single array
    // so it can be uploaded to video car
    unsigned int *indices = (unsigned int *)malloc(mesh->mNumFaces * sizeof(unsigned int) * 3);
    int idx = 0;
    for (uint i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace &face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        for (uint j = 0; j < face.mNumIndices; ++j)
        {
          indices[idx++] = face.mIndices[j];
        }
    }

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, indices, GL_STATIC_DRAW);
  }

  // VBO (uploading to GPU)
  // Vertex Buffer Object
  GLuint vbo = 0;

  // Vertex positions
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, &mesh->mVertices[0], GL_STATIC_DRAW );
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Normals
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, &mesh->mNormals[0], GL_STATIC_DRAW );
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

  GLuint program = ShaderLoader::LoadShaders("src/shaders/triangles.vert", "src/shaders/triangles.frag");
  glUseProgram(program);

  printf("Number of faces: %i\n", mesh->mNumFaces);

  // Matrix that build the persepective
  glm::mat4 perspective = glm::perspective(90.f, 4.f/3.f, 0.1f, 100.f);

  // Camera matrix
  glm::mat4 view = glm::lookAt(
      glm::vec3(0.f,  -2.f,   0.5f), // Camera position, in World Space
      glm::vec3(0,  0.5f, 0), // and looks at
      glm::vec3(0,  0,    1)  // Head is up (set to 0,-1,0 to look upside-down)
  );

  glm::mat4 mvp = perspective * view;

  // Loading matrixes into the shader memory
  int cameraLocBuffer = glGetUniformLocation(program, "mvp");
  glUniformMatrix4fv(cameraLocBuffer, 1, GL_FALSE, glm::value_ptr(mvp));

  float speed = 0.5f; // move at 15 unit per second
  float last_position = 0.0f;
  int matrixLocBuffer = glGetUniformLocation(program, "matrix");

  // Model matrix
  glm::mat4 matrix(1.f);
  // This is for the godzilla only
  // remove if not loading it
  // matrix = glm::scale(matrix, glm::vec3(0.015f, 0.015f, 0.015f));
  // matrix = matrix * glm::yawPitchRoll(0, 0, 90);
  // matrix = glm::rotate(matrix, -90.0f, glm::vec3(1,0,0));
  // matrix = matrix * glm::eulerAngleYXZ(0.0f, 0.0f, 3.14f/2.0f);
  // matrix = matrix * glm::eulerAngleYXZ(0.0f, - 3.1415f/2.0f, 0.0f);
  // glm::quat quaternion;
  // quaternion = glm::normalize(quaternion);

  // matrix = matrix * glm::toMat4(quaternion);

  // Main loop
  while (!glfwWindowShouldClose(engine._window))
  {
    // add a timer for doing animation
    static float previous_seconds = glfwGetTime ();
    float current_seconds = glfwGetTime ();
    float elapsed_seconds = current_seconds - previous_seconds;
    previous_seconds = current_seconds;

    // reverse direction when going to far left or right
    if (fabs(last_position) > 1.0f) {
      speed = -speed;
    }

    // matrix:
    // matrix = glm::rotate(matrix, elapsed_seconds * speed, glm::vec3(1, 0, 0));

    // quaternion
    float angle = elapsed_seconds * speed;
    // quaternion = glm::angleAxis(angle, glm::vec3(1, 0, 0));
    // matrix = matrix * glm::toMat4(quaternion);

    // euler angles
    matrix = matrix * glm::yawPitchRoll(0.f, 0.f, angle);

    glUniformMatrix4fv(matrixLocBuffer, 1, GL_FALSE, glm::value_ptr(matrix));
    glUseProgram(program);

    glBindVertexArray(vao);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, mesh->mNumFaces*3, GL_UNSIGNED_INT, 0);

    engine.swapBuffer();

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (engine._window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(engine._window, 1);
  }

}
