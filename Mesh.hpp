#ifndef MESH_HPP
#define MESH_HPP

namespace TIE {
    class Mesh{
        protected:
        vertices[double*] vertices;
        size_t vertexCount;

        public:
        virtual void Load(char* fileName) = 0;

        virtual void Draw() = 0;
        
    };
}

#endif