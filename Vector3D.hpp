///\file Vector3D.hpp
///\brief Fichier comprenant une classe comprenant tous les calculs de base se faisant avec des vecteurs

#pragma once
#include <cmath>

# define PI 3.14159265358979323846

///\class Vector3D
///\brief Classe comprenant tous les calculs de base se faisant avec des vecteurs
class Vector3D{
public:

double x, y, z; ///< valeur en x, y, z du vecteur

Vector3D(double x, double y, double z){
    this->x = x; 
    this->y = y; 
    this->z = z; 
}

///\brief Retourne la norme du vecteur, donc sa longueur
///\return la norme du vecteur, donc sa longueur
double GetNorm(){
    return sqrt((x * x) + (y * y) + (z * z));
}

///\brief Retourne l'angle situé entre 2 vecteur
///\param v vecteur nécéssaire au calcul de l'angle
///\return l'angle situé entre 2 vecteur
double GetAngle(Vector3D v){
    return acos((*this * v) / (GetNorm() * v.GetNorm())) * 180.0 / PI;
}

///\brief Normalise le vecteur, donc transforme le vecteur en vecteur unitaire
void Normalize(){
    x /= GetNorm();
    y /= GetNorm();
    z /= GetNorm();
}

///\brief Additionne 2 vecteurs ensemble
///\param v vecteur nécéssaire au calcul d'addition
///\return Addition de 2 vecteurs
Vector3D operator+(Vector3D v){
   return Vector3D(x + v.x, y + v.y, z + v.z);
}

///\brief Soustrait 2 vecteurs ensemble
///\param v vecteur nécéssaire au calcul de soustraction
///\return différence entre 2 vecteurs
Vector3D operator-(Vector3D v){
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

///\brief Produit scalaire
///\param v vecteur nécéssaire au calcul du produit scalaire
///\return Produit scalaire
double operator*(Vector3D v){
    return x * v.x + y * v.y + z * v.z;
}

///\brief Produit par un scalaire
///\param s scalaire nécéssaire au calcul du produit par un scalaire
///\return Produit par un scalaire
Vector3D operator*(double s){
    return Vector3D(x * s, y * s, z * s);
}

///\brief Produit vectoriel
///\param v vecteur nécéssaire au calcul du produit vectoriel
///\return Produit vectoriel
Vector3D operator%(Vector3D v){
    return Vector3D((y * v.z) - (v.y * z), (z * v.x) - (v.z * x),(x * v.y) - (v.x * y));
}

};