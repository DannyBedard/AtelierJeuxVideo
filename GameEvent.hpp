#ifndef GAMEEVENT_HPP
#define GEMEEVENT_HPP

#include <SDL2/SDL.h>

namespace TIE{
    class GameEvent {
        private:
            static SDL_Event sdlEvent;
        public:
            static unsigned int GetType(){
                return sdlEvent.type;
            }

            static int Poll(){
                return SDL_PollEvent(&sdlEvent);
            }
    };

    SDL_Event GameEvent::sdlEvent = SDL_Event();
}

#endif