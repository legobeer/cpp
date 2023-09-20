#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include "Cellule.hxx"
#include <vector>

int main()
{
    Univers u = Univers(0, Vecteur(0, 0, 0), Vecteur(0, 0, 0), Vecteur(), 3, 0);
    /* Ajout du Soleil */
    u.addParticule(Particule(Vecteur(0, 0, 0), 1, 0, 0, Vecteur(0, 0, 0)));
    /* Ajout Terre */
    u.addParticule(Particule(Vecteur(0, 1, 0), 3e-6, 0, 1, Vecteur(-1, 0, 0)));
    /* Ajout Jupiter */
    u.addParticule(Particule(Vecteur(0, 5.36, 0), 9.55e-4, 0, 2, Vecteur(-0.425, 0, 0)));
    /* Ajout Haley */
    u.addParticule(Particule(Vecteur(34.75, 0, 0), 1e-14, 0, 3, Vecteur(0, 0.0296, 0)));
    std::vector<Vecteur> fOld(4, Vecteur());
    u.creerCellules();
    u.stromerVerlet(fOld, 468.5, 0.015);
}