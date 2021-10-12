#ifndef TEXTUREMESH3D_HPP
#define TEXTUREMESH3D_HPP

#include "Mesh.hpp"
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

namespace TIE {
    class TextureMesh3D : public Mesh {
        private:
        vector<double> vSommets, vNormals, vTextures, faces;
        public:

        void Load(string fileName){
            ifstream file;
            vector<double> sommetsTMP, normalsTMP, texturesTMP;
            vector<string> lineTMP, facesTMP;
            char lineType;
            file.open(fileName);
            string line;

            getline(file, line, '\n');

            file >> lineType;
            
            while (!file.eof()){
                getline(file, line, '\n');
                lineTMP = Split(line, ' ');

                if(lineTMP[0] == "v"){
                    sommetsTMP.push_back(atof(lineTMP[1].c_str()));
                    sommetsTMP.push_back(atof(lineTMP[2].c_str()));
                    sommetsTMP.push_back(atof(lineTMP[3].c_str()));
                    vertexCount+=3;
                }
                else if(lineTMP[0] == "vt"){
                    texturesTMP.push_back(atof(lineTMP[1].c_str()));
                    texturesTMP.push_back(atof(lineTMP[2].c_str()));
                }
                else if(lineTMP[0] == "vn"){
                    normalsTMP.push_back(atof(lineTMP[1].c_str()));
                    normalsTMP.push_back(atof(lineTMP[2].c_str()));
                    normalsTMP.push_back(atof(lineTMP[3].c_str()));
                }
                else if(lineTMP[0] == "f"){
                    for (int i=1; i<=3; i++){
                        facesTMP = Split(lineTMP[i], '/');
                        faces.push_back(stoi(facesTMP[0]));
                        faces.push_back(stoi(facesTMP[1]));
                        faces.push_back(stoi(facesTMP[2]));
                    }
                }
            }

            for(int i=0; i<faces.size()*1;i+=3){
                vSommets.push_back(sommetsTMP[faces[i] * 3 - 3]);
                vSommets.push_back(sommetsTMP[faces[i] * 3 - 2]);
                vSommets.push_back(sommetsTMP[faces[i] * 3 - 1]);

                vTextures.push_back(texturesTMP[faces[i + 1] * 2 - 2]);
                vTextures.push_back(texturesTMP[faces[i + 1] * 2 - 1]);

                vNormals.push_back(normalsTMP[faces[i + 2] * 3 - 3]);
                vNormals.push_back(normalsTMP[faces[i + 2] * 3 - 2]);
                vNormals.push_back(normalsTMP[faces[i + 2] * 3 - 1]);
            }

        }

         vector<string> Split(string line, char splitChar){
            istringstream ss(line);
            string token;
            vector<string> splitLine;

            while(getline(ss, token, splitChar)) {
                splitLine.push_back(token);
	        }

            return splitLine;
        }

        void Draw(){
            unsigned int crateTextureId;
            glGenTextures(1.0, &crateTextureId);
            glBindTexture(GL_TEXTURE_2D, crateTextureId);

            SDL_Surface* sdlSurface = IMG_Load("crate.png");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
            SDL_FreeSurface(sdlSurface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, crateTextureId);
            double textures[vertexCount * 2];
            double sommets[vertexCount * 3];
            double normals[vertexCount * 3];

            for(int i=0; i<vertexCount * 3; i++)
                sommets[i] = vSommets[i];
            
            for(int i=0; i<vertexCount * 2; i++)
                textures[i] = vTextures[i];

            for(int i=0; i<vertexCount * 3;i++)
                normals[i] = vNormals[i];

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glVertexPointer(3, GL_DOUBLE, 0, sommets);//3 pour 3D, type de donnée, commence à la case 0 du tableau, tableau contenant les sommets
            glNormalPointer(GL_DOUBLE, 0, normals); //Les normals sont toujours en 3D
            glTexCoordPointer(2, GL_DOUBLE, 0, textures);

            glDrawArrays(GL_TRIANGLES, 0, vertexCount);//Ce qu'on mettais dans le GL_Begin, à partir de 0, combien de sommet à afficher
        }
    };
}

#endif