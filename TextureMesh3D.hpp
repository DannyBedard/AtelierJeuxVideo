#ifndef TEXTUREMESH3D_HPP
#define TEXTUREMESH3D_HPP

#include "Mesh.hpp"
#include <fstream>

namespace TIE {
    class TextureMesh3D{
        private:
        std::fstream file;

        public:

        void Load(string fileName){
            double x, y, z;
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
                        break;
                    }

            }
        }

        void Draw(){

        }
        
    };
}

#endif