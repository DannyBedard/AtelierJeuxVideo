#ifndef ENGINEE_HPP
#define ENGINEE_HPP

#include <cmath>

#include "Engine.hpp"
#include "GLContext.hpp"
#include "GameEvent.hpp"
#include "Matrix44D.hpp"
#include "Vector3D.hpp"
#include "FirstPersonCamera.hpp"
#include "EventDispatcher.hpp"
#include "TextureMesh3D.hpp"

using namespace std;

namespace TIE{
    class Engine3D : public Engine<Engine3D>{
        private:
        GLContext glContext;
        EventDispatcher eventDispatcher;
        TextureMesh3D texture;
        TTF_Font* ttfFont;

        public:
        FirstPersonCamera camera = FirstPersonCamera(0.0, 0.0, 10.0);

        Engine3D(){
            SDL_Init(SDL_INIT_EVERYTHING);
            IMG_Init(IMG_INIT_PNG);
            TTF_Init(); //Essentiel, ça compile, mais la font va être nullptr (0x0)

            ttfFont = TTF_OpenFont("LafayetteComicPro.ttf", 42);

            eventDispatcher.Bind(SDL_KEYDOWN, &camera);
            eventDispatcher.Bind(SDL_KEYUP, &camera);
            eventDispatcher.Bind(SDL_MOUSEMOTION, &camera);
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
            SDL_SetRelativeMouseMode(SDL_TRUE); 

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
            sdlSurface = TTF_RenderText_Blended(ttfFont, "Hola Mundo", {255, 255, 255, 220});
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
            int fontWidth = sdlSurface->w, fontHeight = sdlSurface->h;
            SDL_FreeSurface(sdlSurface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            //Déclaration Matrice et angle de rotation
            Matrix44D perspectiveProjection;
            Matrix44D orthogonalProjection;
            Matrix44D rotateX;
            Matrix44D rotateY;
            Matrix44D rotateZ;
            SDL_Point windowSize = glContext.GetSize();
            orthogonalProjection.LoadOrthogonal(windowSize.x, windowSize.y);
            double angleX = 0.0005;
            double angleY = 0.0003;
            double angleZ = 0.0007;
            rotateX.LoadRotateX(angleX);
            rotateY.LoadRotateY(angleY);
            rotateZ.LoadRotateZ(angleZ);

            texture.Load("crate.obj");

            size_t vertexCount = 24;
            double vertices[vertexCount * 3] = {
                -1.0, 1.0, 1.0,1.0, 1.0, 1.0,1.0, -1.0, 1.0, -1.0, -1.0, 1.0,
                -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0,
                -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 
                1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 
                -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0}; // * 3 composante par sommet

            double normals[vertexCount * 3] = {
                0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
                0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
                1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0
            };
            
            double textureCoords[vertexCount * 2] = {
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            }; //6 face * 4 sommet * 2
            

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
                        default:
                            eventDispatcher.Dispatch();
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

                    //Vecteur Normal (Lumière)
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

                    //Vidage de la fenêtre
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //Gestion de l'affichage
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
                    camera.Update();
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glMultMatrixd(perspectiveProjection.matrix);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    // Application de la matrice de vue
                    camera.ApplyView();

                    glBindTexture(GL_TEXTURE_2D, crateTextureId);

                    glEnableClientState(GL_VERTEX_ARRAY);
                    glEnableClientState(GL_NORMAL_ARRAY);
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                    glVertexPointer(3, GL_DOUBLE, 0, vertices);//3 pour 3D, type de donnée, commence à la case 0 du tableau, tableau contenant les sommets
                    glNormalPointer(GL_DOUBLE, 0, normals); //Les normals sont toujours en 3D
                    glTexCoordPointer(2, GL_DOUBLE, 0, textureCoords);

                    glDrawArrays(GL_QUADS, 0, vertexCount);//Ce qu'on mettais dans le GL_Begin, à partir de 0, combien de sommet à afficher
                    
                    glContext.Refresh(); 
                    // Incrémenter une variable qui serra affichée
                    // le réinitialiser quand le chrono passe une seconde
                
            }
        }       
            void draw(){
                glEnable(GL_TEXTURE_2D);
                GLuint texture;
                glGenTextures(1,&texture);

                unsigned char texture_data[2][2][4] =
                                {
                                    0,0,0,255,  255,255,255,255,
                                    255,255,255,255,    0,0,0,255
                                };

                glBindTexture(GL_TEXTURE_2D,texture);
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                GL_NEAREST);

                glBegin(GL_QUADS);

                glTexCoord2f(0.0,0.0);  glVertex3f(-50.0,-5.0,-50.0);
                glTexCoord2f(25.0,0.0);  glVertex3f(50.0,-5.0,-50.0);
                glTexCoord2f(25.0,25.0);  glVertex3f(50.0,-5.0,50.0);
                glTexCoord2f(0.0,25.0);  glVertex3f(-50.0,-5.0,50.0);

                glEnd();

                glDisable(GL_TEXTURE_2D);
            }
    };
}

#endif