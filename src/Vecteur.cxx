#include "Vecteur.hxx"
#include <cmath>
#include <random>
#include "Exception.hxx"

Vecteur::Vecteur(double x, double y, double z) : x(x), y(y), z(z) {}

double Vecteur::getX() const { return x; }

double Vecteur::getY() const { return y; }

double Vecteur::getZ() const { return z; }

void Vecteur::setX(double x) { this->x = x; }

void Vecteur::setY(double y) { this->y = y; }

void Vecteur::setZ(double z) { this->z = z; }

void Vecteur::setVecteur(const Vecteur &vecteur) { *this = vecteur; }

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
    std::cout << v.x << " " << v.y << " " << v.z;
    return os;
}

Vecteur Vecteur::attributionMaillage(double rCut) const
{
    Vecteur maillage = *this;
    maillage.setX(static_cast<int>(maillage.getX() / rCut));
    maillage.setY(static_cast<int>(maillage.getY() / rCut));
    maillage.setZ(static_cast<int>(maillage.getZ() / rCut));
    return maillage;
}

Vecteur Vecteur::getDirection(const Vecteur &vecteur) const
{
    return Vecteur(vecteur.getX() - getX(), vecteur.getY() - getY(), vecteur.getZ() - getZ());
}

double Vecteur::computeDistance2(const Vecteur &vecteur) const
{
    const double dx = getX() - vecteur.getX();
    const double dy = getY() - vecteur.getY();
    const double dz = getZ() - vecteur.getZ();

    const double distance2 = dx * dx + dy * dy + dz * dz;
    return distance2;
}

std::vector<Vecteur> Vecteur::getVoisins(int nombreDimension) const
{
    std::vector<Vecteur> voisins;
    try
    {
        dimensionInvalide(nombreDimension);
    }
    catch (const DimensionInvalide &e)
    {
        std::cout << e.what() << std::endl;
    }
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

void dimensionInvalide(int nombreDimension)
{
    if (!(nombreDimension > 0 && nombreDimension < 4))
        throw DimensionInvalide();
}

void vecteurInvalide(int nombreDimension, const Vecteur &vecteur)
{
    try
    {
        dimensionInvalide(nombreDimension);
    }
    catch (DimensionInvalide &e)
    {
        std::cout << e.what() << std::endl;
    }
    if (nombreDimension == 1 && (vecteur.getY() != 0 || vecteur.getZ()))
        throw ProblemeVecteurDimension();
    if (nombreDimension == 2 && vecteur.getZ() != 0)
        throw ProblemeVecteurDimension();
}

void invalidBorne(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension)
{
    try
    {
        dimensionInvalide(nombreDimension);
    }
    catch (DimensionInvalide &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        vecteurInvalide(nombreDimension, borneInf);
        vecteurInvalide(nombreDimension, borneSup);
    }
    catch (ProblemeVecteurDimension &e)
    {
        std::cout << e.what() << std::endl;
    }
    Vecteur tmp = borneInf;
    tmp = -tmp + borneSup;
    if (nombreDimension > 0)
    {
        if (tmp.getX() <= 0)
            throw InvalidBorneException();
    }
    if (nombreDimension > 1)
    {
        if (tmp.getY() <= 0)
            throw InvalidBorneException();
    }
    if (nombreDimension > 2)
    {
        if (tmp.getZ() <= 0)
            throw InvalidBorneException();
    }
}

Vecteur randomVecteur(int nombreDimension, const Vecteur &borneInf, const Vecteur &borneSup)

{
    std::random_device rd;
    std::mt19937 mt(rd());
    double x = 0, y = 0, z = 0;
    if (nombreDimension > 0)
    {
        std::uniform_real_distribution<double> dist(borneInf.getX(), borneSup.getX());
        x = dist(mt);
    }
    if (nombreDimension > 1)
    {
        std::uniform_real_distribution<double> dist(borneInf.getY(), borneSup.getY());
        y = dist(mt);
    }
    if (nombreDimension > 2)
    {
        std::uniform_real_distribution<double> dist(borneInf.getZ(), borneSup.getZ());
        z = dist(mt);
    }
    return Vecteur(x, y, z);
}