#include "Game.hpp"
#include "Player.hpp"
#include "Scene.hpp"

using namespace std;

void Topaz::Game::init(Engine::Core &engine)
{
  _player = new Player();
  _player->matrix = glm::translate(_player->matrix, glm::vec3(-1, 0, 0));
  engine.addGameObject(_player);

  _scene = new Scene();
  engine.addGameObject(_scene);
}

void Topaz::Game::tick(Engine::Core &engine)
{
}
