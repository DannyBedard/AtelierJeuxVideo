#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#define keyW keys[0]
#define keyA keys[1]
#define keyS keys[2]
#define keyD keys[3]
#define keySpace keys[4]
#define mouseMotion keys[5]

#include <iostream>
#include "Vector3D.hpp"
#include "Observer.hpp"

namespace TIE {
    class Camera3D : public Observer{
        private:
        Vector3D position;
        Matrix44D viewMatrix;
        Vector3D target;
        Vector3D up;

        bool keys [6] = {false, false, false, false, false, false};

        public:

        Camera3D(double x, double y, double z){
            viewMatrix.LoadIdentity();
            target = Vector3D (0.0, 0.0, 0.0);
            up = Vector3D(0.0, 1.0, 0.0);
            position = Vector3D(x, y, z);
        }
        /*Camera3D(Vector3D v){
            viewMatrix.LoadIdentity();
            target = Vector3D (0.0, 0.0, -1.0);
            actualPosition = Vector3D (0.0, 0.0, 0.0);
            up = Vector3D(0.0, 1.0, 0.0);
            position = Vector3D(v.x, v.y, v.z);
        }*/

        void ApplyView(){
            // Multiplier la matrice de vue
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glMultMatrixd(viewMatrix.matrix);
            glTranslated(-position.x, -position.y, -position.z);
        }

        //Va devenir virtuel pure
        void Update(){
            if(mouseMotion) {
                RotateVision(GameEvent::GetRelMouseX, GameEvent::GetRelMouseY);
            }

            if(keyW) {
                position.z += 0.001;
            }
            if(keyS) position.z -= 0.001;
            if(keyA) position.x += 0.001;
            if(keyD) position.x -= 0.001;
            if(keySpace) 
                position.y += 0.001; 
            else if (position.y > 0.0)
                position.y -= 0.001; 
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
                    case SDL_MOUSEMOTION:
                        mouseMotion = true;
                        break;
                    break;
            };
        }
    };
    
}

#endif