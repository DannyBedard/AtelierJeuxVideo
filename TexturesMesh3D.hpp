#ifndef TEXTUREMESH3D_HPP
#define TEXTUREMESH3D_HPP

#include "Mesh.hpp"
#include <fstream>

namespace TIE {
    class TextureMesh3D : public Mesh{
        private:
        std::fstream file;

        public:
        void Load(char* fileName){
            double x, y, z;
            char lineType;
            file.open(fileName);

            switch(lineType){
                case '#':

                break;
                case 'v':
            }
        }

        void Draw(){

        }
        
    };
}

#endif