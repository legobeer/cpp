#pragma once
#include <list>
#include "Particule.hxx"

class Cellule
{
private:
    list<Particule> particules;
    list<Cellule> cellulesVoisines;

public:
    Cellule(list<Particule>, list<Cellule>);

    list<Particule> getParticules();

    list<Cellule> getCellulesVoisines();

    void addParticule(Particule particule);

    void addCelluleVoisine(Cellule celluleVoisine);
};