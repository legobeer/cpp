#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <vector>

int main()
{
    Univers u = Univers(0, Vecteur(0, 0, 0), Vecteur(0, 0, 0), 1);
    list<Particule> &particules = u.getParticules();
    /* Ajout du Soleil */
    particules.push_back(Particule(Vecteur(0, 0, 0), Vecteur(0, 0, 0), 1, 0, 0));
    /* Ajout Terre */
    particules.push_back(Particule(Vecteur(0, 1, 0), Vecteur(-1, 0, 0), 3e-6, 0, 1));
    /* Ajout Jupiter */
    particules.push_back(Particule(Vecteur(0, 5.36, 0), Vecteur(-0.425, 0, 0), 9.55e-4, 0, 2));
    /* Ajout Haley */
    particules.push_back(Particule(Vecteur(34.75, 0, 0), Vecteur(0, 0.0296, 0), 1e-14, 0, 3));
    u.display();
    vector<Vecteur> fOld(4, Vecteur(0, 0, 0));
    u.stromerVerlet(fOld, 468.5, 1);
    u.display();
}