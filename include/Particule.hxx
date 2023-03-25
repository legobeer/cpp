#pragma once
#include "Vecteur.hxx"
#include <list>
#include <vector>

using namespace std;

class Particule
{
private:
    Vecteur position;
    Vecteur vitesse;
    Vecteur force;
    double masse;
    int type;
    int id;

public:
    Particule(Vecteur, Vecteur, double, int, int);

    Vecteur getVitesse();
    Vecteur getPosition();
    Vecteur *getForce();
    int getId();
    double getMasse();

    Vecteur forceParticule(Particule);

    void updatePosition(double);

    void updateVitesse(double, Vecteur);
};

void stromerVerlet(list<Particule> &, vector<Vecteur> &, double, double);

void initialisationForces(list<Particule> &);