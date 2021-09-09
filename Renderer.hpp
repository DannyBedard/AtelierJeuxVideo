#ifndef GLContext_HPP
#define GLContext

#include <SDL2/SDL.h>

#include <SDL2/SDL.h>
#include "Window.hpp"

namespace TIE {
    class Renderer : public Window{
        public:
        SDL_Renderer* sdlRenderer;

        Renderer(const int& width = 640, const int& height = 480, const char* title = "", const int& x = SDL_WINDOWPOS_CENTERED, const int& y = SDL_WINDOWPOS_CENTERED, const unsigned int windowFlags = 0, const unsigned int rendererFlags = 0) : Window(title, x, y, width, height, windowFlags){
            sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);
        }

        void Refresh(){
            SDL_RenderPresent(sdlRenderer);
        }

        ~Renderer(){
            SDL_DestroyRenderer(sdlRenderer);
        }
    };
}

#endif