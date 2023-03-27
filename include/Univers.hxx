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
    double lD;
    double rCut;

public:
    Univers(int, Vecteur, Vecteur, int);

    Univers(int, Vecteur, Vecteur, int, double, double);

    list<Particule> &getParticules();

    int getNombreParticules();

    void stromerVerlet(vector<Vecteur> &, double, double);

    void initialisationForces();

    void display();
};

Particule creerParticule(Vecteur, Vecteur, int, int);
