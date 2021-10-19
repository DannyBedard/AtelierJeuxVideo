#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include <cmath>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"
#include "Matrix44D.hpp"
#include "Vector3D.hpp"
#include "FirstPersonCamera.hpp"
#include "EventDispatcher.hpp"
#include "TextureMesh3D.hpp"
#include "Chrono.hpp"

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;
        EventDispatcher eventDispatcher;
        TextureMesh3D texture;
        TTF_Font* ttfFont;

        public:
        FirstPersonCamera camera = FirstPersonCamera(0.0, 0.0, 10.0);
        Chrono chrono = Chrono();

        Engine3D(){
            SDL_Init(SDL_INIT_EVERYTHING);
            IMG_Init(IMG_INIT_PNG);
            TTF_Init(); //Essentiel, ça compile, mais la font va être nullptr (0x0)

            eventDispatcher.Bind(SDL_KEYDOWN, &camera);
            eventDispatcher.Bind(SDL_KEYUP, &camera);
            eventDispatcher.Bind(SDL_MOUSEMOTION, &camera);

            ttfFont = TTF_OpenFont("LafayetteComicPro.ttf", 42);
        }
        ~Engine3D(){
            eventDispatcher.Unbind(SDL_KEYDOWN, &camera);
            eventDispatcher.Unbind(SDL_KEYUP, &camera);
            eventDispatcher.Unbind(SDL_MOUSEMOTION, &camera);

            TTF_CloseFont(ttfFont);

            TTF_Quit();
            SDL_Quit();
        }

        void Start(){
            // Commutateurs OpenGL
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //SDL_SetRelativeMouseMode(SDL_TRUE); 

            // Chargement de la texture du caisson
            unsigned int crateTextureId;
            glGenTextures(1.0, &crateTextureId);
            glBindTexture(GL_TEXTURE_2D, crateTextureId);

            SDL_Surface* sdlSurface = IMG_Load("crate.png");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
            SDL_FreeSurface(sdlSurface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            // Chargement de la texture du texte
            unsigned int fontTextureId;
            glGenTextures(1.0, &fontTextureId);
            glBindTexture(GL_TEXTURE_2D, fontTextureId);

            //Chargement Maillage
            texture.Load("crate.obj");

            //angle de rotation du maillage
            double angleX = 0.0005, angleY = 0.0003, angleZ = 0.0007;

            // Frustum
            SDL_Point windowSize = glContext.GetSize();
            double right = tan(45.0 * 3.14159 / 180.0) * 1.0;
            double top = ((double)windowSize.y / (double)windowSize.x) * right;

            //Déclaration Matrice et angle de rotation
            Matrix44D perspectiveProjection;
            Matrix44D orthogonalProjection;
            Matrix44D rotateX;
            Matrix44D rotateY;
            Matrix44D rotateZ;
            
            orthogonalProjection.LoadOrthogonal(windowSize.x, windowSize.y);

            rotateX.LoadRotateX(angleX);
            rotateY.LoadRotateY(angleY);
            rotateZ.LoadRotateZ(angleZ);

            perspectiveProjection.LoadPerspective(right, top, 1.0, 100.0);
    

            int frame = 0;
            int frameCount = 0;
            bool isOpen = true;
            int fontWidth, fontHeight;
            while(isOpen){
                while(GameEvent::Poll()){
                    switch(GameEvent::GetType()){
                        case SDL_QUIT: 
                            isOpen = false;
                            break;
                        default:
                            eventDispatcher.Dispatch();
                            break;
                    }
                }
                    // Gestion des mises à jour
                    camera.Update();
                    
                    //Affichage seconde
                    if (chrono.GetElapsedSeconds() > 1.0){
                        frameCount = frame;
                        frame = 0;
                        glBindTexture(GL_TEXTURE_2D, fontTextureId);
                        chrono.Reset();

                    std::string s = std::to_string(frameCount);
                    char const *pchar = s.c_str();
                    
                    sdlSurface = TTF_RenderText_Blended(ttfFont, pchar, {255, 255, 255, 220});
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
                    fontWidth = sdlSurface->w, fontHeight = sdlSurface->h;
                    SDL_FreeSurface(sdlSurface);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    }
                    
                    frame ++;

                    // Gestion de l'affichage
                    //Vidage de la fenêtre
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    //Mode 2D
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(orthogonalProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();

                    glBindTexture(GL_TEXTURE_2D, fontTextureId);
                    glBegin(GL_QUADS);
                        glTexCoord2d(0.0, 0.0);  glVertex3d(0.0, 0.0, 0.0);
                        glTexCoord2d(1.0, 0.0);  glVertex3d((double)fontWidth, 0.0, 0.0);
                        glTexCoord2d(1.0, 1.0);  glVertex3d((double)fontWidth, (double)fontHeight, 0.0);
                        glTexCoord2d(0.0, 1.0);  glVertex3d(0.0, (double)fontHeight, 0.0);
                    glEnd();

                    //Mode 3D
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(perspectiveProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    // Application de la matrice de vue
                    camera.ApplyView();

                    //Rotation du caisson

                    // Affichage du caisson
                    floor(crateTextureId);
                    texture.Draw(crateTextureId);
                    
                    //Rafraichissement de la fenêtre
                    glContext.Refresh(); 
                
            }
            glDeleteTextures(1, &crateTextureId);
            glDeleteTextures(2, &fontTextureId);
        }       
        //Dessin plancher
            void floor(GLuint texture){
                glBindTexture(GL_TEXTURE_2D, texture);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0,0.0);  glVertex3f(-50.0,-5.0,-50.0);
                glTexCoord2f(25.0,0.0);  glVertex3f(50.0,-5.0,-50.0);
                glTexCoord2f(25.0,25.0);  glVertex3f(50.0,-5.0,50.0);
                glTexCoord2f(0.0,25.0);  glVertex3f(-50.0,-5.0,50.0);

                glEnd();
            }
    };
}

#endif