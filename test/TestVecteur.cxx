#include "Vecteur.hxx"
#include <iostream>

using namespace std;

int main()
{
    Vecteur vecteur1 = Vecteur(1.0, 2.0, 3.5);
    Vecteur vecteur2 = Vecteur(1.2, 3.0, 5.5);
    double scalar = 2.5;
    cout << vecteur1 << "\n"
         << (vecteur1 *= scalar) << "\n"
         << (vecteur1 += vecteur2) << "\n"
         << vecteur1.getDirection(vecteur2) << "\n";

    Vecteur r;
    r = 2;
    cout << r << endl;
}