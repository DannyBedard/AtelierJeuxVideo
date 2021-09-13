#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"
#include "Matrix44D.hpp"
#include "Vector3D.hpp"

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;

        public:
        void Start(){
            Matrix44D orthogonalProjection;
            orthogonalProjection.LoadOrthogonal(640.0, 480.0);
            bool isOpen = true;
            Vector3D vector = Vector3D(0.0, 0.0, 0.0);
            double reboundX = 0.05;
            double reboundY = 0.05;
            double size = 100.0;
            while(isOpen){

                if(vector.x + size >= glContext.GetSize().x || vector.x < 0.0)
                    reboundX = -reboundX;
                if(vector.y + size >= glContext.GetSize().y || vector.y < 0.0)
                    reboundY = -reboundY;
                vector.x += reboundX;
                vector.y += reboundY;

                while(GameEvent::Poll()){
                    switch(GameEvent::GetType()){
                        case SDL_QUIT: 
                            isOpen = false;
                            break;
                        case SDL_KEYDOWN:
                            glColor3d(0.0, 0.0, 1.0);
                            break;
                        case SDL_KEYUP:
                            glColor3d(1.0, 1.0, 1.0);
                            break;

                    }
                }
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(orthogonalProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();

                    glClear(GL_COLOR_BUFFER_BIT);
                    glBegin(GL_QUADS); 
                        glVertex3d(vector.x, vector.y, vector.z);
                        glVertex3d(vector.x + size, vector.y, vector.z);
                        glVertex3d(vector.x + size, vector.y + size, vector.z);
                        glVertex3d(vector.x, vector.y + size, vector.z);
                    glEnd();

                    glContext.Refresh(); 
                
            }
        }
    };
}

#endif