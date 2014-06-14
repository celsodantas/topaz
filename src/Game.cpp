#include "Game.hpp"
#include "Player.hpp"

using namespace std;

Topaz::Game::Game(Engine::Core engine) : _engine(engine) {

  Player *player = new Player();
  Player *player2 = new Player();

  player->matrix = glm::translate(player->matrix, glm::vec3(-1, 0, 0));
  player2->matrix = glm::translate(player2->matrix, glm::vec3(1, 0, 0));

  _gameObjects.push_back(player);
  _gameObjects.push_back(player2);
}

void Topaz::Game::run() {
  // This should
  _running = true;

  while (_running)
  {
    _engine.prepareNewRender();

    for (int i = 0; i < _gameObjects.size(); i++)
    {
      auto object = _gameObjects[i];
      _engine.draw(object);
    }

    _engine.swapBuffer();

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey (_engine._window, GLFW_KEY_ESCAPE))
      _running = false;
  }

  glfwSetWindowShouldClose(_engine._window, 1);
}
