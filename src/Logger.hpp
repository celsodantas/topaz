#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <SDL2/SDL.h>

namespace Topaz {

  class Logger {
  public:
    static void print(std::string text) {
      std::cout << text << std::endl;
    }
  };
}

#endif