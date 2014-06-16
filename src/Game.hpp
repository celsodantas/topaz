#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "engine/Core.hpp"

namespace Topaz {
  using namespace std;
  class Player;
  class Scene;

  class Game {
  public:
    Game() {};
    void init(Engine::Core &engine);
    void tick(Engine::Core &engine);

  private:

    bool _running = false;

    Player *_player;
    Scene *_scene;
  };
}

#endif
