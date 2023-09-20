#include "Univers.hxx"
#include <ostream>

int main()
{
    Univers u = Univers(1, Vecteur(), Vecteur(1, 1), Vecteur(1, 1), 2, 0.5, ConditionLimite::Absorption, -120, 0, true);
    std::vector<Vecteur> fOld(1, 0);
    u.stromerVerlet(fOld, 1, 0.005);
}