#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include "Camera3D.hpp"
#include "Observer.hpp"
#include "GameEvent.hpp"

namespace TIE {
    class FirstPersonCamera : public Camera3D{
        public:
        FirstPersonCamera(double x, double y, double z){
            viewMatrix.LoadIdentity();
            target = Vector3D (0.0, 0.0, 0.0);
            up = Vector3D(0.0, 1.0, 0.0);
            position = Vector3D(x, y, z);
        }

        void Update(){
            if(mouseMotion) {
                SDL_Point mouseRel = GameEvent::GetRelMouse();
                RotateVision(mouseRel.x / 1000, mouseRel.y / 1000);
                mouseMotion = false;
            }

            if(keyW) position.z -= 0.01;
            if(keyS) position.z += 0.01;
            if(keyA) position.x -= 0.01;
            if(keyD) position.x += 0.01;
            if(keySpace) 
                position.y += 0.01; 
            else if (position.y > 0.0)
                position.y -= 0.01;
        }

        void RotateVision(double angleX, double angleY){
            Matrix44D matrixRotationX;
            Matrix44D matrixRotationY;
            matrixRotationX.LoadRotateX(angleX);
            matrixRotationY.LoadRotateY(angleY);

            Vector3D front = target - position;
            front = matrixRotationY * front;
            front.Normalize();
            Vector3D side = front % up;
            side.Normalize();
            up = side % front;
            up.Normalize();

            viewMatrix.LoadView(front, side, up);
        }

        void Notification(){
            switch(GameEvent::GetType()){
                case SDL_KEYUP:
                    switch(GameEvent::GetKey()){
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
                    switch(GameEvent::GetKey()){
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
                case SDL_MOUSEMOTION:
                mouseMotion = true;
                break;
            };
        }
    };
}

#endif