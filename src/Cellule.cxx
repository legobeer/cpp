#include "Particule.hxx"
#include "Cellule.hxx"
#include <list>

Cellule::Cellule(list<Particule> particules, list<Vecteur> cellulesVoisines)
{
    this->cellulesVoisines = cellulesVoisines;
    this->particules = particules;
}

list<Particule> Cellule::getParticules()
{
    return this->particules;
}

list<Vecteur> Cellule::getCellulesVoisines()
{
    return this->cellulesVoisines;
}

void Cellule::addParticule(Particule particule)
{
    this->particules.push_back(particule);
}

void Cellule::addCelluleVoisine(Vecteur celluleVoisine)
{
    this->cellulesVoisines.push_back(celluleVoisine);
}