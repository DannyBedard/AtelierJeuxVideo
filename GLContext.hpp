#ifndef GLContext_HPP
#define GLContext_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Window.hpp"

namespace TIE {
    class GLContext : public Window{
        private:
            SDL_GLContext glContext;
        public:
            GLContext (const int& width = 640, const int& height = 480, const char* title = "", const int& x = SDL_WINDOWPOS_CENTERED, const int& y = SDL_WINDOWPOS_CENTERED, const unsigned int windowFlags = 0, const unsigned int rendererFlags = 0) : Window(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL){
                glContext = SDL_GL_CreateContext(sdlWindow);
            }

            void Refresh(){
                SDL_GL_SwapWindow(sdlWindow);
            }

            ~GLContext(){
                SDL_GL_DeleteContext(glContext);
                SDL_DestroyWindow(sdlWindow);
            }
    };
}

#endif