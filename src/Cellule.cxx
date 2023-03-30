#include "Particule.hxx"
#include "Cellule.hxx"
#include <unordered_set>

std::unordered_set<Particule, Particule::HashParticule> Cellule::getParticules()
{
    return this->particules;
}

std::unordered_set<Vecteur, Vecteur::HashVecteur> Cellule::getCellulesVoisines()
{
    return this->cellulesVoisines;
}

void Cellule::addParticule(Particule particule)
{
    this->particules.insert(particule);
}

void Cellule::addCelluleVoisine(Vecteur celluleVoisine)
{
    this->cellulesVoisines.insert(celluleVoisine);
}

void Cellule::deleteParticule(Particule particule)
{
    this->particules.erase(particule);
}

void Cellule::deleteVoisin(Vecteur voisin)
{
    this->cellulesVoisines.erase(voisin);
}