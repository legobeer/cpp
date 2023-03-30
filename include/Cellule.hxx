#pragma once
#include <unordered_set>
#include "Particule.hxx"
#include "Vecteur.hxx"

class Cellule
{
private:
    std::unordered_set<Particule, Particule::HashParticule> particules;
    std::unordered_set<Vecteur, Vecteur::HashVecteur> cellulesVoisines;

public:
    std::unordered_set<Particule, Particule::HashParticule> getParticules();

    std::unordered_set<Vecteur, Vecteur::HashVecteur> getCellulesVoisines();

    void addParticule(Particule);

    void addCelluleVoisine(Vecteur);

    void deleteParticule(Particule);

    void deleteVoisin(Vecteur);
};
