#include "Vecteur.hxx"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

Vecteur::Vecteur()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vecteur::Vecteur(double x)
{
    this->x = x;
    this->y = 0;
    this->z = 0;
}

Vecteur::Vecteur(double x, double y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
}

Vecteur::Vecteur(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vecteur::getX() { return x; }

double Vecteur::getY() { return y; }

double Vecteur::getZ() { return z; }

void Vecteur::setXInt(int x) { this->x = x; }

void Vecteur::setYInt(int y) { this->y = y; }

void Vecteur::setZInt(int z) { this->z = z; }

void Vecteur::setVecteur(Vecteur vecteur) { *this = vecteur; }

void Vecteur::multiplyScalar(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vecteur::addVectors(Vecteur vecteur)
{
    x += vecteur.getX();
    y += vecteur.getY();
    z += vecteur.getZ();
}

void Vecteur::subVectors(Vecteur vecteur)
{
    x -= vecteur.getX();
    y -= vecteur.getY();
    z -= vecteur.getZ();
}

Vecteur Vecteur::attributionMaillage(double rCut)
{
    Vecteur maillage = (*this);
    maillage.setXInt((int)(maillage.getX() / rCut));
    maillage.setYInt((int)(maillage.getY() / rCut));
    maillage.setZInt((int)(maillage.getZ() / rCut));
    return maillage;
}

Vecteur Vecteur::getDirection(Vecteur vecteur)
{
    Vecteur direction = Vecteur();
    direction.addVectors(vecteur);
    direction.subVectors(*this);
    return direction;
}

double Vecteur::computeDistance(Vecteur vecteur)
{
    double distance = pow(vecteur.getX() - x, 2) + pow(vecteur.getY() - y, 2) + pow(vecteur.getZ() - z, 2);
    return pow(distance, 0.5);
}

void Vecteur::displayVector()
{
    cout << "(" << x << ", " << y << ", " << z << ")\n";
}
