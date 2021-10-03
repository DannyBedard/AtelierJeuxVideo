#ifndef TEXTUREMESH3D_HPP
#define TEXTUREMESH3D_HPP

#include "Mesh.hpp"
#include <fstream>
#include <bits/stdc++.h>

namespace TIE {
    class TextureMesh3D{
        private:
        std::fstream file;
        vector<double> sommets, normals, textures, faces;
        public:

        void Load(string fileName){
            double x, y, z;
            int faceIndex;
            char lineType;
            file.open(fileName);

            file >> lineType;
            
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
                            sommets.push_back(x);
                            sommets.push_back(y);
                            sommets.push_back(z);
                            break;
                        
                        case 't':
                            file >> x;
                            file >> y;
                            textures.push_back(x);
                            textures.push_back(y);
                            break;
                        
                        case 'n':
                            file >> x;
                            file >> y;
                            file >> z;
                            normals.push_back(x);
                            normals.push_back(y);
                            normals.push_back(z);
                            break;
                        
                    }
                case 'f':
                    file >> lineType;
                    file >> faceIndex;
                    sommets[(faceIndex - 1) * 3];
                    sommets[(faceIndex - 1) * 3 + 1];
                    sommets[(faceIndex - 1) * 3 + 1];
                    break;
            }
        }

        void Draw(){

        }
        
    };
}

#endif