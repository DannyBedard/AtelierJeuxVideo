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

            static double GetRelMouseX(){
                return static_cast<double>(sdlEvent.motion.xrel);
            }

            static double GetRelMouseY(){
                return static_cast<double>(sdlEvent.motion.yrel);
            }
    };

    SDL_Event GameEvent::sdlEvent = SDL_Event();
}

#endif