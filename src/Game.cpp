#include "Game.hpp"
#include "Player.hpp"

using namespace std;

Topaz::Game::Game(Engine engine) : _engine(engine) {

  Player *player = new Player(_engine);

  _gameObjects.push_back(player);

  // No need to call this now
  // as the loop is inside the Player class
  //engine.swapBuffer();

}

void Topaz::Game::run() {

  while (!glfwWindowShouldClose(_engine._window))
  {
    for (int i = 0; i < _gameObjects.size(); i++)
    {
      auto object = _gameObjects[i];
      _engine.draw(object);
    }

    _engine.swapBuffer();

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (_engine._window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(_engine._window, 1);
  }


}
