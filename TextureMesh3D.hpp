#ifndef TEXTUREMESH3D_HPP
#define TEXTUREMESH3D_HPP

#include "Mesh.hpp"
#include <fstream>
#include <bits/stdc++.h>

namespace TIE {
    class TextureMesh3D : public Mesh {
        private:
        std::fstream file;
        vector<double> vSommets, vNormals, vTextures, faces;
        public:

        void Load(string fileName){
            vector<double> sommetsTMP, normalsTMP, texturesTMP, facesTMP;
            double x, y, z;
            int faceIndex;
            char lineType;
            file.open(fileName);

            file >> lineType;
            
            while (lineType != EOF){
                switch(lineType){
                    case '#':
                    break;
                    case 'v':
                        file >> lineType;
                        switch (lineType)
                        {
                            case ' ':
                                file >> x;
                                file >> y;
                                file >> z;
                                sommetsTMP.push_back(x);
                                sommetsTMP.push_back(y);
                                sommetsTMP.push_back(z);
                                vertexCount+=3;
                                break;
                            
                            case 't':
                                file >> x;
                                file >> y;
                                texturesTMP.push_back(x);
                                texturesTMP.push_back(y);
                                break;
                            
                            case 'n':
                                file >> x;
                                file >> y;
                                file >> z;
                                normalsTMP.push_back(x);
                                normalsTMP.push_back(y);
                                normalsTMP.push_back(z);
                                break;
                            
                        }
                    case 'f':
                    for (int i=0; i<9; i++){
                        file >> lineType;
                        file >> faceIndex;
                        faces.push_back(faceIndex);
                    }
                        break;
                }
            }

            for(int i=0; i<facesTMP.size();i+=3){
                vSommets.push_back(sommetsTMP[facesTMP[i] * 3 - 3]);
                vSommets.push_back(sommetsTMP[facesTMP[i] * 3 - 2]);
                vSommets.push_back(sommetsTMP[facesTMP[i] * 3 - 1]);

                vTextures.push_back(texturesTMP[facesTMP[i + 1] * 2 - 2]);
                vTextures.push_back(texturesTMP[facesTMP[i + 1] * 2 - 1]);

                vNormals.push_back(normalsTMP[facesTMP[i + 2] * 3 - 3]);
                vNormals.push_back(normalsTMP[facesTMP[i + 2] * 3 - 2]);
                vNormals.push_back(normalsTMP[facesTMP[i + 2] * 3 - 1]);
            }
        }

        void Draw(){
            double textures[vertexCount * 2];
            double sommets[vertexCount * 3];
            double normals[vertexCount * 3];

            for(int i=0; i<vSommets.size();i++)
                sommets[i] = vSommets[i];
            
            for(int i=0; i<vTextures.size();i++)
                textures[i] = vTextures[i];

            for(int i=0; i<vNormals.size();i++)
                normals[i] = vNormals[i];

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glVertexPointer(3, GL_DOUBLE, 0, sommets);//3 pour 3D, type de donnée, commence à la case 0 du tableau, tableau contenant les sommets
            glNormalPointer(GL_DOUBLE, 0, normals); //Les normals sont toujours en 3D
            glTexCoordPointer(2, GL_DOUBLE, 0, textures);

            glDrawArrays(GL_QUADS, 0, vertexCount);//Ce qu'on mettais dans le GL_Begin, à partir de 0, combien de sommet à afficher
        }
        
    };
}

#endif