#include "Particule.hxx"
#include "Cellule.hxx"
#include <unordered_set>

const std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> &Cellule::getParticules() const
{
    return this->particules;
}

std::unordered_set<Vecteur, Vecteur::HashVecteur> Cellule::getCellulesVoisines()
{
    return this->cellulesVoisines;
}

void Cellule::addParticule(std::shared_ptr<Particule> particule)
{
    this->particules.insert(particule);
}

void Cellule::addCelluleVoisine(Vecteur celluleVoisine)
{
    this->cellulesVoisines.insert(celluleVoisine);
}

void Cellule::deleteParticule(std::shared_ptr<Particule> particule)
{
    this->particules.erase(particule);
}

void Cellule::deleteVoisin(Vecteur voisin)
{
    this->cellulesVoisines.erase(voisin);
}
