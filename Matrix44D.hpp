#ifndef MATRIX44D_HPP
#define MATRIX44D_HPP

#define m11 matrix[0]
#define m12 matrix[1]
#define m13 matrix[2]
#define m14 matrix[3]
#define m21 matrix[4]
#define m22 matrix[5]
#define m23 matrix[6]
#define m24 matrix[7]
#define m31 matrix[8]
#define m32 matrix[9]
#define m33 matrix[10]
#define m34 matrix[11]
#define m41 matrix[12]
#define m42 matrix[13]
#define m43 matrix[14]
#define m44 matrix[15]

#include <math.h>
#include "Vector3D.hpp"

namespace TIE {
    class Matrix44D{
    private:
        void Swap(double i1, double i2){
            double swap = i1;
            i1 = i2;
            i2 = i1;
        }
    public:
        double matrix[16];

        void LoadIdentity(){
            m11 = m22 = m33 = m44 = 1.0;
            m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0;
        }

        // glOrtho
        void LoadOrthogonal(double right, double bottom){
            m11 = 2.0 / right;
            m22 = 2.0 / -bottom;
            m33 = m41 = -1.0;
            m42 = m44 = 1.0;
            m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m43 = 0.0;
        }

        // glFrustum
        void LoadPerspective(double right, double top, double nearCut, double farCut){
            m11 = nearCut / right;
            m22 = nearCut / top;
            m33 = -(farCut + nearCut) / (farCut - nearCut);
            m34 = -1.0;
            m43 = (-2.0 * farCut * nearCut) / (farCut - nearCut);
            m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m41 = m42 = m44 = 0.0;
        }

        void Transpose(){
            Swap(m12, m21);
            Swap(m13, m31);
            Swap(m14, m41);
            Swap(m23, m32);
            Swap(m24, m42);
            Swap(m34, m43);
        }

        void LoadRotateX(double angle){
            m11 = 1.0;
            m12 = m13 = m21 = m31 = 0.0;
            m22 = cos(angle);
            m23 = -sin(angle);
            m32 = sin(angle);
            m33 = cos(angle);
        }

        void LoadRotateY(double angle){
            m11 = cos(angle);
            m12 = m21 = m23 = m32 = 0.0;
            m13 = sin(angle);
            m22 = 1.0;
            m31 = -sin(angle);
            m33 = cos(angle);
        }

        void LoadRotateZ(double angle){
            m11 = cos(angle);
            m12 = -sin(angle);
            m13 = m23 = m31 = m32 = 0.0;
            m21 = sin(angle);
            m22 = cos(angle);
            m33 = 1.0;
        }

        void LoadView(Vector3D front, Vector3D side, Vector3D top){
            m11 = side.x;
            m21 = side.y;
            m31 = side.z;
            m12 = side.x;
            m22 = side.y;
            m32 = side.z;
            m13 = -front.x;
            m23 = -front.y;
            m33 = -front.y;
            m44 = 1.0;
            m41 = m42 = m43 = m14 = m24 = m34 = 0.0;
        }

       Vector3D operator*(Vector3D v){
            v.x = m11 * v.x + m12 * v.y + m13 * v.z;
            v.y = m21 * v.x + m22 * v.y + m23 * v.z;
            v.z = m31 * v.x + m32 * v.y + m33 * v.z;

            return v;
        }
    };
}

#endif