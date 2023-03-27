#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <vector>
#include <list>
#include <map>

class Univers
{
private:
    list<Particule> particules;
    int nombreParticules;
    Vecteur borneInf;
    Vecteur borneSup;
    int nombreDimension;
    double lD;
    double rCut;
    map<Vecteur, Cellule> cellules;

public:
    Univers(int, Vecteur, Vecteur, int);

    Univers(int, Vecteur, Vecteur, int, double, double);

    list<Particule> getParticules();

    int getNombreParticules();

    void creerCellules();

    void addParticule(Particule);

    void stromerVerlet(vector<Vecteur>, double, double);

    void initialisationForces();

    void display();
};

Particule creerParticule(Vecteur, Vecteur, int, int);
