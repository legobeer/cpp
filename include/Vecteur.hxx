#pragma once
#include <list>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

class Vecteur
{
private:
    double x;
    double y;
    double z;

public:
    Vecteur(double = 0, double = 0, double = 0);

    Vecteur operator+(const Vecteur &);

    Vecteur &operator+=(const Vecteur &);

    Vecteur operator-() const;

    Vecteur operator-(const Vecteur &);

    Vecteur &operator*=(double);

    Vecteur operator*(double);

    Vecteur &operator*=(const Vecteur &);

    Vecteur &operator-=(const Vecteur &);

    Vecteur &operator=(double);

    bool operator==(const Vecteur &otherVecteur) const;

    friend std::ostream &operator<<(std::ostream &, const Vecteur &);

    double getX();

    double getY();

    double getZ();

    void setXInt(int);

    void setYInt(int);

    void setZInt(int);

    void setVecteur(Vecteur);

    Vecteur attributionMaillage(double);

    std::vector<Vecteur> getVoisins(int);

    double computeDistance(Vecteur);

    Vecteur getDirection(Vecteur);

    struct HashVecteur
    {
        size_t operator()(const Vecteur &vecteur) const
        {
            std::string tmp = std::to_string(vecteur.x) + "," + std::to_string(vecteur.y) + "," + std::to_string(vecteur.z);

            int hashCode = 0;
            for (size_t i = 0; i < tmp.length(); i++)
            {
                hashCode += tmp[i] * pow(31, i);
            }
            return hashCode;
        }
    };
};
