#ifndef CORE_HPP
#define CORE_HPP

#include <vector>

#define GLFW_INCLUDE_GLCOREARB
#include <glfw/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonHeader.hpp"
#include "engine/GameObject.hpp"
#include "engine/Camera.hpp"

namespace Topaz {
  class GameObject;
  class Game;

  namespace Engine {

    struct Cursor {
      double x, y, deltaX, deltaY;
      bool btn1Pressed, btn2Pressed;
    };

    class Core {
    public:
      Core(Game *game);

      void initialize();
      void prepareNewRender();
      void swapBuffer();
      void quit();

      void draw(GameObject *object);

      void setShaderMVP(uint32 shaderId);

      Cursor cursor;
      void updateCursorData();

      float deltaTime;
      void updateDeltaData();

      void run();
      void addGameObject(GameObject *sobject);

      GLFWwindow   *_window;
      Camera       camera;

    private:

      int _winWidth  = 800;
      int _winHeight = 600;
      bool _running = true;

      void initWindow();
      void initGL();

      std::vector<GameObject*> _gameObjects;
      Game *_game;
    };
  }
}

#endif
