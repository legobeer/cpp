#include <list>
#include <vector>
#include <bits/stdc++.h>
#include "Vecteur.hxx"
#include "Particule.hxx"

using namespace std;

Particule::Particule(Vecteur position, Vecteur vitesse, double masse, int type, int id)
{
    this->position = position;
    this->vitesse = vitesse;
    this->force = Vecteur(0, 0, 0);
    this->masse = masse;
    this->type = type;
    this->id = id;
}

Vecteur Particule::getVitesse() { return vitesse; }
Vecteur Particule::getPosition() { return position; }
Vecteur *Particule::getForce() { return &force; }
int Particule::getId() { return id; }
double Particule::getMasse() { return masse; }

Vecteur Particule::forceParticule(Particule particule)
{
    Vecteur direction = position.getDirection(particule.getPosition());
    direction.multiplyScalar(masse * particule.getMasse());
    direction.multiplyScalar(pow(position.computeDistance(particule.getPosition()), -3));
    direction.addVectors(force);
    return direction;
}

void Particule::updatePosition(double gammaT)
{
    Vecteur fParticule = force;
    fParticule.multiplyScalar(0.5 * masse * gammaT);
    fParticule.addVectors(vitesse);
    fParticule.multiplyScalar(gammaT);
    position.addVectors(fParticule);
}

void Particule::updateVitesse(double gammaT, Vecteur fOld)
{
    Vecteur fParticule = force;
    fParticule.addVectors(fOld);
    fParticule.multiplyScalar(0.5 * gammaT * masse);
    vitesse.addVectors(fParticule);
}

void stromerVerlet(list<Particule> &particules, vector<Vecteur> &fOld, double tEnd, double gammaT)
{
    /* Initialisation des forces */
    initialisationForces(particules);
    double t = 0;
    int i = 0;
    while (t < tEnd)
    {
        t += gammaT;
        for (Particule &particule : particules)
        {
            particule.updatePosition(gammaT);
            fOld[i] = *particule.getForce();
            i++;
        }
        /* Calcul des forces */
        initialisationForces(particules);
        i = 0;
        for (Particule &particule : particules)
        {
            particule.updateVitesse(gammaT, fOld[i]);
            i++;
        }
    }
}

void initialisationForces(list<Particule> &particules)
{
    int iemeParticule = 0, jiemeParticule;
    Vecteur Fij;
    for (Particule &particuleI : particules)
    {
        jiemeParticule = 0;
        for (Particule &particuleJ : particules)
        {
            if (iemeParticule >= jiemeParticule)
                continue;
            Fij = particuleI.forceParticule(particuleJ);
            particuleI.getForce()->addVectors(Fij);
            Fij.multiplyScalar(-1);
            particuleJ.getForce()->addVectors(Fij);
            jiemeParticule++;
        }
        iemeParticule++;
    }
}