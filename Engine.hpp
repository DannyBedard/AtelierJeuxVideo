#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "GameEvent.hpp"
#include "Singleton.hpp"

namespace TIE {
  template <typename T>
  class Engine : public Singleton<T> {
  public:
    //virtual void start() = 0;
  };
}

#endif