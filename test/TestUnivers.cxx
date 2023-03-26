#include "Univers.hxx"
#include <iostream>

int main()
{
    Univers u = Univers(3, Vecteur(0, 0, 0), Vecteur(1, 1, 1), 3);
    u.display();
    vector<Vecteur> fOld(u.getNombreParticules(), Vecteur(0, 0, 0));
    u.display();
    cout << "\n\n";
    u.stromerVerlet(fOld, 485, 15);
    u.display();
}