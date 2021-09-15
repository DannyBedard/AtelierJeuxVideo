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

namespace TIE {
    class Matrix44D{
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

        

        //Matrice * vecteur
        //Matrice Rotation
    };
}