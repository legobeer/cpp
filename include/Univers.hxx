#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include <vector>
#include <list>

class Univers
{
private:
    list<Particule> particules;
    int nombreParticules;
    Vecteur borneInf;
    Vecteur borneSup;
    int nombreDimension;

public:
    Univers(int, Vecteur, Vecteur, int);

    list<Particule> &getParticules();

    int getNombreParticules();

    void stromerVerlet(vector<Vecteur> &, double, double);

    void initialisationForces();

    void display();
};

Particule creerParticule(Vecteur, Vecteur, int, int);
