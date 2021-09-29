#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include <SDL2/SDL.h>

namespace TIE{
    class GameEvent {
        private:
            static SDL_Event sdlEvent;
        public:
            static char GetKey(){
                return sdlEvent.key.keysym.sym;
            }

            static unsigned int GetType(){
                return sdlEvent.type;
            }

            static int Poll(){
                return SDL_PollEvent(&sdlEvent);
            }

            static SDL_Point GetRelMouse(){
                SDL_Point position;
                position.x = sdlEvent.motion.xrel;
                position.y = sdlEvent.motion.yrel;
                return position;
            }
    };

    SDL_Event GameEvent::sdlEvent = SDL_Event();
}

#endif