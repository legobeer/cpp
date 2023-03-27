#pragma once
#include <list>
#include "Particule.hxx"
#include "Vecteur.hxx"

class Cellule
{
private:
    list<Particule> particules;
    list<Vecteur> cellulesVoisines;

public:
    list<Particule> getParticules();

    list<Vecteur> getCellulesVoisines();

    void addParticule(Particule particule);

    void addCelluleVoisine(Vecteur celluleVoisine);
};