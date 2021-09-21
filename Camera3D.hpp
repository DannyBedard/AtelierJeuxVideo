#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#define keyW keys[0]
#define keyA keys[1]
#define keyS keys[2]
#define keyD keys[3]
#define keySpace keys[4]

#include "Vector3D.hpp"
#include "Observable.hpp"

namespace TIE {
    class Camera3D : public Observer{
        private:
        Vector3D position;

        bool keys [5] = {false, false, false, false, false};

        public:

        Camera3D(double x, double y, double z){
            position = Vector3D(x, y, z);
            //position.x = x;
            //position.y = y;
            //position.z = z;
        }
        Camera3D(Vector3D v){
            position = Vector3D(v.x, v.y, v.z);
            //position.x = v.x;
            //position.y = v.y;
            //position.z = v.z;
        }

        void ApplyView(){
            glTranslated(position.x, position.y, position.z);
        }

        void Notification(){
            switch(GameEvent::GetType()){
                case SDL_KEYUP:
                    switch(GameEvent::getKey()){
                        case SDLK_w:
                            keyW = false;
                        break;

                        case SDLK_a:
                            keyA = false;
                        break;

                        case SDLK_s:
                            keyS = false;
                        break;

                        case SDLK_d:
                            keyD = false;
                        break;

                        case SDLK_SPACE:
                            keySpace = false;
                        break;
                    };
                    break;

                case SDL_KEYDOWN:
                    switch(GameEvent::getKey()){
                        case SDLK_w:
                            keyW = true;
                        break;

                        case SDLK_a:
                            keyA = true;
                        break;

                        case SDLK_s:
                            keyS = true;
                        break;

                        case SDLK_d:
                            keyD = true;
                        break;

                        case SDLK_SPACE:
                            keySpace = true;
                        break;
                    };
                    break;
            };
        }

        void Update(){
            if(keyW) position.z -= 0.001;
            if(keyS) position.z += 0.001;
            if(keyA) position.x -= 0.001;
            if(keyD) position.x += 0.001;
            if(keySpace) 
                position.y += 0.001; 
            else if (position.y > 0.0)
                position.y -= 0.001; 
        }

    };
    
}

#endif