#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

namespace TIE {

    class Window{
        protected:
        SDL_Window* sdlWindow;
        public:
        virtual void Refresh() = 0;

        Window(const char* title, const int& x, const int& y, const int& width, const int& height, const unsigned int flags){
            sdlWindow = SDL_CreateWindow(title, x, y, width, height, flags);
        }

        virtual ~Window() {
            SDL_DestroyWindow(sdlWindow);
        }

        void SetTitle(const char* title){
            SDL_SetWindowTitle(sdlWindow, title);
        }

        SDL_Point GetSize() {
            SDL_Point windowSize;
            SDL_GetWindowSize(sdlWindow, &windowSize.x, &windowSize.y);
            return windowSize;
        }
    };
}

#endif
