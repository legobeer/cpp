#pragma once
class Vecteur
{
private:
    double x;
    double y;
    double z;

public:
    Vecteur();
    Vecteur(double);
    Vecteur(double, double);
    Vecteur(double, double, double);

    double getX();

    double getY();

    double getZ();

    void setXInt(int);

    void setYInt(int);

    void setZInt(int);

    void setVecteur(Vecteur);

    void multiplyScalar(double);

    void addVectors(Vecteur);

    void subVectors(Vecteur);

    Vecteur attributionMaillage(double);

    double computeDistance(Vecteur);

    Vecteur getDirection(Vecteur);

    void displayVector();
};
