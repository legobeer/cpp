#include "Univers.hxx"
#include <iostream>

int main()
{
    Univers u = Univers(3, Vecteur(0, 0, 0), Vecteur(1, 1, 1), 3);
    std::cout << u << std::endl;
    std::vector<Vecteur> fOld(u.getNombreParticules(), Vecteur(0, 0, 0));
    std::cout << u << std::endl;
    std::cout << "\n\n";
    u.stromerVerlet(fOld, 485, 15);
    std::cout << u << std::endl;
}