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

std::vector<Vecteur> Vecteur::getVoisins(int nombreDimension)
{
    std::vector<Vecteur> voisins;
    for (int xOffset = -1; xOffset < 2; xOffset++)
    {
        if (nombreDimension > 1)
        {
            for (int yOffset = -1; yOffset < 2; yOffset++)
            {
                if (nombreDimension > 2)
                {
                    for (int zOffset = -1; zOffset < 2; zOffset++)
                    {
                        if (!(zOffset == 0 && yOffset == 0 && xOffset == 0))
                            voisins.push_back(Vecteur(x + xOffset, y + yOffset, z + zOffset));
                    }
                }
                else if (!(yOffset == 0 && xOffset == 0))
                {
                    voisins.push_back(Vecteur(x + xOffset, y + yOffset, z));
                }
            }
        }
        else if (xOffset != 0)
            voisins.push_back(Vecteur(x + xOffset, y, z));
    }
    return voisins;
}
