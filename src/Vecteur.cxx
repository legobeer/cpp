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

list<Vecteur> Vecteur::getVoisins(int nombreDimension)
{
    int y, z = 0;
    list<Vecteur> voisins;
    for (int x = -1; x < 2; x++)
    {
        if (nombreDimension > 1)
        {
            for (y = -1; y < 2; y++)
            {
                for (z = -1; z < 2; z++)
                {
                    if (nombreDimension == 1 && x != 0)
                        voisins.push_back(Vecteur(this->x - x));
                    else if (nombreDimension == 2 && x != 0 && y != 0)
                        voisins.push_back(Vecteur(this->x - x, this->y - y));
                    else if (nombreDimension == 3 && x != 0 && y != 0 && z != 0)
                        voisins.push_back(Vecteur(this->x - x, this->y - y, this->z - z));
                }
            }
        }
    }
    return voisins;
}

int Vecteur::hashCode(Vecteur lD)
{
    return (int)(lD.getX() * lD.getY() * z + y * lD.getX() + x);
}

void Vecteur::displayVector()
{
    cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vecteur intToVecteur(Vecteur lD, int hashCode)
{
    int z = hashCode / (lD.getX() * lD.getY());
    hashCode -= z * lD.getX() * lD.getY();
    int y = hashCode / lD.getX();
    hashCode -= y * lD.getX();
    int x = hashCode;
    return Vecteur(x, y, z);
}
