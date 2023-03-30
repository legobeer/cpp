#include "Vecteur.hxx"
#include <bits/stdc++.h>

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

Vecteur Vecteur::operator+(const Vecteur &rhs)
{
    Vecteur lhs = *this;
    lhs += rhs;
    return lhs;
}

Vecteur Vecteur::operator-(const Vecteur &rhs)
{
    Vecteur lhs = *this;
    lhs -= rhs;
    return lhs;
}

Vecteur &Vecteur::operator*=(const Vecteur &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vecteur Vecteur::operator-() const
{
    return Vecteur(-x, -y, -z);
}

Vecteur &Vecteur::operator-=(const Vecteur &rhs)
{
    *this += -rhs;
    return *this;
}

Vecteur &Vecteur::operator+=(const Vecteur &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vecteur &Vecteur::operator*=(double scalaire)
{
    x *= scalaire;
    y *= scalaire;
    z *= scalaire;
    return *this;
}

Vecteur Vecteur::operator*(double scalaire)
{
    Vecteur lhs = *this;
    lhs *= scalaire;
    return lhs;
}

Vecteur &Vecteur::operator=(double v)
{
    x = v;
    y = v;
    z = v;
    return *this;
}

bool Vecteur::operator==(const Vecteur &otherVecteur) const
{
    if (this->x == otherVecteur.x && this->y == otherVecteur.y && this->z == otherVecteur.z)
        return true;
    else
        return false;
};

std::ostream &operator<<(std::ostream &os, const Vecteur &v)
{
    std::cout << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
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
    return vecteur - *this;
}

double Vecteur::computeDistance(Vecteur vecteur)
{
    Vecteur tmp = (*this - vecteur);
    tmp *= tmp;
    return pow(tmp.getX() + tmp.getY() + tmp.getZ(), 0.5);
}

std::list<Vecteur> Vecteur::getVoisins(int nombreDimension)
{
    int y, z = 0;
    std::list<Vecteur> voisins;
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

double Vecteur::coordonneesMax()
{
    double max = x;
    if (x < y)
        max = y;
    if (max < z)
        max = z;
    return max;
}

double Vecteur::coordonneesMin()
{
    double min = x;
    if (x > y)
        min = y;
    if (min > z)
        min = z;
    return z;
}
