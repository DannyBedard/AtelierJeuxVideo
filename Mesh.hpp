#ifndef MESH_HPP
#define MESH_HPP

#include <stdlib.h>

namespace TIE {
    class Mesh{
        protected:
        double* vertices;
        size_t vertexCount = 0;

        public:
        virtual void Load(string fileName) = 0;

        virtual void Draw() = 0;
    };
}

#endif