#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include <cmath>
#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"
#include "Matrix44D.hpp"
#include "Vector3D.hpp"

using namespace std;

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;

        public:
        void Start(){
            unsigned int textureId;
            glGenTextures(1.0, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            SDL_Surface* sdlSurface = IMG_Load("crate.png");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
            SDL_FreeSurface(sdlSurface);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            Matrix44D perspectiveProjection;
            Matrix44D orthogonalProjection;
            SDL_Point windowSize = glContext.GetSize();
            orthogonalProjection.LoadOrthogonal(windowSize.x, windowSize.y);

            double right = tan(45.0 * 3.14159 / 180.0) * 1.0;
            double top = ((double)windowSize.y / (double)windowSize.x) * right;
            perspectiveProjection.LoadPerspective(right, top, 1.0, 100.0);

            Vector3D v1(-1.0, 1.0, -1.0);
            Vector3D v2(1.0, 1.0, -1.0);
            Vector3D v3(1.0, 1.0, 1.0);
            Vector3D v4(-1.0, 1.0, 1.0);
            Vector3D v5(-1.0, -1.0, -1.0);
            Vector3D v6(1.0, -1.0, -1.0);
            Vector3D v7(1.0, -1.0, 1.0);
            Vector3D v8(-1.0, -1.0, 1.0);

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);

            bool isOpen = true;
            while(isOpen){
                while(GameEvent::Poll()){
                    switch(GameEvent::GetType()){
                        case SDL_QUIT: 
                            isOpen = false;
                            break;
                    }
                }

                    // TODO : HANDLE UPDATE

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(perspectiveProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();

                    glTranslated(0.0, 0.0, -3.0);

                    glBegin(GL_QUADS);
                        //AVANT
                        glTexCoord2d(0.0, 0.0); glVertex3d(v4.x, v4.y, v4.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
                        //ARRIERE
                        glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v5.x, v5.y, v5.z);
                        //DESSUS
                        glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v4.x, v4.y, v4.z);
                        //DESSOUS
                        glTexCoord2d(0.0, 0.0); glVertex3d(v5.x, v5.y, v5.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
                        //DROIT
                        glTexCoord2d(0.0, 0.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        //GAUCHE
                        glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v4.x, v4.y, v4.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v5.x, v5.y, v5.z);

                    glEnd(); 

                    // TODO 3D
                    /*glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(orthogonalProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();*/
                    // TODO 2D

                    glContext.Refresh(); 
                
            }
        }
    };
}

#endif