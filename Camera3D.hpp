#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#define keyW keys[0]
#define keyA keys[1]
#define keyS keys[2]
#define keyD keys[3]
#define keySpace keys[4]
#define mouseMotion keys[5]

#include <iostream>
#include "Vector3D.hpp"
#include "Observer.hpp"
#include "GLContext.hpp"

namespace TIE {
    class Camera3D : public Observer{
        protected:
        Vector3D position;
        Matrix44D viewMatrix;
        Vector3D target;
        Vector3D up;

        bool keys [6] = {false, false, false, false, false, false};

        public:

        Camera3D(){}

        Camera3D(double x, double y, double z){
            viewMatrix.LoadIdentity();
            target = Vector3D (0.0, 0.0, 0.0);
            up = Vector3D(0.0, 1.0, 0.0);
            position = Vector3D(x, y, z);
        }

        virtual void Update() = 0;

        void ApplyView(){
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glMultMatrixd(viewMatrix.matrix);
            glTranslated(-position.x, -position.y, -position.z);
        }

    };
    
}

#endif