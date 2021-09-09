#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;

        public:
        void Start(){
            bool isOpen = true;
            while(isOpen){
                while(GameEvent::Poll()){
                    switch(GameEvent::GetType()){
                        case SDL_QUIT: 
                            isOpen = false;
                            break;
                    }
                    glContext.Refresh();
                }
            }
        }
    };
}

#endif