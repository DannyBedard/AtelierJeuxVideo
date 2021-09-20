#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include <cmath>

#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"
#include "Matrix44D.hpp"
#include "Vector3D.hpp"
#include "Camera3D.hpp"
#include "observable.hpp"

using namespace std;

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;
        Observable keyUp, keyDown;
        Camera3D camera;

        public:
        camera = Camera3D(0.0, 0.0, -5.0);

        Engine3D(){
            SDL_Init(SDL_INIT_EVERYTHING);
            IMG_Init(IMG_INIT_PNG);
            TTF_Init();
            keyDown.AddObserver(&camera);
            keyUp.AddObserver(&camera);
        }

        void Start(){
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

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
            Matrix44D rotateX;
            Matrix44D rotateY;
            Matrix44D rotateZ;
            SDL_Point windowSize = glContext.GetSize();
            orthogonalProjection.LoadOrthogonal(windowSize.x, windowSize.y);
            double angleX = 0.00005;
            double angleY = 0.00003;
            double angleZ = 0.00007;
            rotateX.LoadRotateX(angleX);
            rotateY.LoadRotateY(angleY);
            rotateZ.LoadRotateZ(angleZ);

            double right = tan(45.0 * 3.14159 / 180.0) * 1.0;
            double top = ((double)windowSize.y / (double)windowSize.x) * right;
            perspectiveProjection.LoadPerspective(right, top, 1.0, 100.0);

            //Vecteur Cube
            Vector3D v1(-1.0, 1.0, -1.0);
            Vector3D v2(1.0, 1.0, -1.0);
            Vector3D v3(1.0, 1.0, 1.0);
            Vector3D v4(-1.0, 1.0, 1.0);
            Vector3D v5(-1.0, -1.0, -1.0);
            Vector3D v6(1.0, -1.0, -1.0);
            Vector3D v7(1.0, -1.0, 1.0);
            Vector3D v8(-1.0, -1.0, 1.0);

            //Vecteur Normal
            Vector3D nFront(0.0, 0.0, 1.0);
            Vector3D nNear(0.0, 0.0, -1.0);
            Vector3D nTop(0.0, 1.0, 0.0);
            Vector3D nBottom(0.0, -1.0, 0.0);
            Vector3D nRight(1.0, 0.0, 0.0);
            Vector3D nLeft(-1.0, 0.0, 0.0);

            bool isOpen = true;
            while(isOpen){
                while(GameEvent::Poll()){
                    switch(GameEvent::GetType()){
                        case SDL_QUIT: 
                            isOpen = false;
                            break;
                        case SDL_KEYUP:
                            keyUp.Notify();
                        break;
                        case SDL_KEYDOWN:
                            keyDown.Notify();
                        break;
                    }
                }

                    // TODO : HANDLE UPDATE
                    
                    //Multiplication par rotation

                    //Cube
                    v1 = rotateX * v1;
                    v2 = rotateX * v2;
                    v3 = rotateX * v3;
                    v4 = rotateX * v4;
                    v5 = rotateX * v5;
                    v6 = rotateX * v6;
                    v7 = rotateX * v7;
                    v8 = rotateX * v8;

                    v1 = rotateY * v1;
                    v2 = rotateY * v2;
                    v3 = rotateY * v3;
                    v4 = rotateY * v4;
                    v5 = rotateY * v5;
                    v6 = rotateY * v6;
                    v7 = rotateY * v7;
                    v8 = rotateY * v8;

                    v1 = rotateZ * v1;
                    v2 = rotateZ * v2;
                    v3 = rotateZ * v3;
                    v4 = rotateZ * v4;
                    v5 = rotateZ * v5;
                    v6 = rotateZ * v6;
                    v7 = rotateZ * v7;
                    v8 = rotateZ * v8;

                    //Veceur Normal (Lumière)
                    nFront = rotateX * nFront;
                    nNear = rotateX * nNear;
                    nTop = rotateX * nTop;
                    nBottom = rotateX * nBottom;
                    nRight = rotateX * nRight;
                    nLeft = rotateX * nLeft;
                    
                    nFront = rotateY * nFront;
                    nNear = rotateY * nNear;
                    nTop = rotateY * nTop;
                    nBottom = rotateY * nBottom;
                    nRight = rotateY * nRight;
                    nLeft = rotateY * nLeft;

                    nFront = rotateZ * nFront;
                    nNear = rotateZ * nNear;
                    nTop = rotateZ * nTop;
                    nBottom = rotateZ * nBottom;
                    nRight = rotateZ * nRight;
                    nLeft = rotateZ * nLeft;



                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    camera.Update();

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(perspectiveProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();

                    camera.ApplyView();

                    glBegin(GL_QUADS);
                        //AVANT
                        glNormal3d(nFront.x, nFront.y, nFront.z);
                        glTexCoord2d(0.0, 0.0); glVertex3d(v4.x, v4.y, v4.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
                        //ARRIERE
                        glNormal3d(nNear.x, nNear.y, nNear.z);
                        glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v5.x, v5.y, v5.z);
                        //DESSUS
                        glNormal3d(nTop.x, nTop.y, nTop.z);
                        glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v4.x, v4.y, v4.z);
                        //DESSOUS
                        glNormal3d(nBottom.x, nBottom.y, nBottom.z);
                        glTexCoord2d(0.0, 0.0); glVertex3d(v5.x, v5.y, v5.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
                        //DROIT
                        glNormal3d(nRight.x, nRight.y, nRight.z);
                        glTexCoord2d(0.0, 0.0); glVertex3d(v3.x, v3.y, v3.z);
                        glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
                        glTexCoord2d(1.0, 1.0); glVertex3d(v6.x, v6.y, v6.z);
                        glTexCoord2d(0.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
                        //GAUCHE
                        glNormal3d(nLeft.x, nLeft.y, nLeft.z);
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