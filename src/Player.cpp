#include <vector>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include "Logger.hpp"
#include "Player.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

// #include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
// #include <SDL2/SDL_opengl.h>

#include <OpenGL/glu.h>
#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>
#include "engine/ShaderLoader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unistd.h>

typedef unsigned char BYTE;
using namespace std;

Topaz::Player::Player() 
{
  GLFWwindow   *_window;

  int _winWidth  = 800;
  int _winHeight = 600;

    if ( glfwInit() < 0 ) 
  {
      std::cout << "Error initializing glfwInit() in " << __FILE__ << ":" << __LINE__ << std::endl;
      exit( EXIT_FAILURE );
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  if ( !(_window = glfwCreateWindow(800, 600, "Title", 0, 0)) ) 
  {
      // closeWindow();
      glfwTerminate();
      std::cout << "Error opening windows glfwCreateWindow() in " << __FILE__ << ":" << __LINE__ << std::endl;
      exit( EXIT_FAILURE );
  }
    
  glfwMakeContextCurrent(_window);


  //////////////////////////////////


  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( _3dModelPath, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  if(!scene)
  {
    Logger::print( importer.GetErrorString() );
  } 
  else 
  {
    Logger::print("Scene loaded");
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

  // // faces
  // int qtdFaces = mesh->mNumFaces;
  // for (int i = 0; i < qtdFaces; i++)
  // {
  //   const aiFace& face = mesh->mFaces[i];
    
  //   for (int k = 0; k < 3; k++)
  //   {
  //     aiVector3D pos    = mesh->mVertices[face.mIndices[k]];
  //     // aiVector3D uv     = mesh->mTextureCoords[0][face.mIndices[k]];
  //     aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);

  //     data.push_back(pos);
  //     data.push_back(normal);
  //     // data.insert(data.end(), (BYTE*)&pos, (BYTE*)&pos + sizeof(aiVector3D));
  //     // data.insert(data.end(), (BYTE*)&uv, (BYTE*)&uv + sizeof(aiVector2D));
  //     // data.insert(data.end(), (BYTE*)&normal, (BYTE*)&normal + sizeof(aiVector3D));
  //     indexCount ++;
  //   }
  // }

  // static const GLfloat vertices[] = {
  //   -1.0f, -1.0f, 0.0f,
  //   1.0f, -1.0f, 0.0f,
  //   0.0f,  1.0f, 0.0f,
  // };

  // std::vector<GLfloat> data(std::begin(vertices), std::end(vertices));
  // data = std::vector<GLfloat>(std::begin(vertices), std::end(vertices));
  // data.insert(data.end(), vertices, vertices + 6);

  // VAO
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // EBO
  {
    // create array with faces
    // have to convert from Assimp format to array
    unsigned int *faceArray;
    faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
    unsigned int faceIndex = 0;
    
    for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
        const aiFace* face = &mesh->mFaces[t];
    
        memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
        faceIndex += 3;
    }

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
  }  

  // VBO (uploading to GPU)
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
  
  GLuint program = ShaderLoader::LoadShaders("/Users/celsodantas/code/cpp/topaz/src/shaders/triangles.vert", "/Users/celsodantas/code/cpp/topaz/src/shaders/triangles.frag");
  glUseProgram(program);

  // glm::mat4 view = glm::lookAt(
  //     glm::vec3(1.2f, 1.2f, 1.2f),
  //     glm::vec3(0.0f, 0.0f, 0.0f),
  //     glm::vec3(0.0f, 0.0f, 1.0f)
  // );
  // GLint uniView = glGetUniformLocation(program, "view");
  // glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  printf("%i\n", mesh->mNumFaces);

  float matrix[] = {
    1.0f, 0.0f, 0.0f, 0.0f, // first column
    0.0f, 1.0f, 0.0f, 0.0f, // second column
    0.0f, 0.0f, 1.0f, 0.0f, // third column
    0.0f, 0.0f, 0.0f, 1.0f  // fourth column
  };

  float speed = 1.0f; // move at 1 unit per second
  float last_position = 0.0f;
  int matrix_location = glGetUniformLocation(program, "matrix");

  while (!glfwWindowShouldClose(_window)) 
  {
    // add a timer for doing animation
    static double previous_seconds = glfwGetTime ();
    double current_seconds = glfwGetTime ();
    double elapsed_seconds = current_seconds - previous_seconds;
    previous_seconds = current_seconds;

    // reverse direction when going to far left or right
    if (fabs(last_position) > 1.0f) {
      speed = -speed;
    }

    matrix[6] = elapsed_seconds * speed + last_position;
    matrix[9] = elapsed_seconds * speed + last_position;
    last_position = matrix[6];
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
    glUseProgram(program);

    glBindVertexArray(vao);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, mesh->mNumFaces*3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(_window);

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (_window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(_window, 1);
  }


  // glDrawArrays(GL_TRIANGLES, 0, mesh->mNumFaces);
}
