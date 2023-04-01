#include "Univers.hxx"
#include "Particule.hxx"
#include <iostream>

int main()
{
    Particule p(Vecteur(1, 2, 3), 1.0, 0, 0, Vecteur(4, 5, 6));
    p.setForce(Vecteur(7, 8, 9));
    double gammaT = 0.1;
    p.updatePosition(gammaT);
    std::cout << p.getPosition() << std::endl;
}