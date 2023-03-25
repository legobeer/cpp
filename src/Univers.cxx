#include "Univers.hxx"
#include "Vecteur.hxx"
#include "Particule.hxx"
#include <vector>
#include <list>
#include <iostream>
#include <bits/stdc++.h>
#include <random>
using namespace std;

Univers::Univers(int nombreParticules, Vecteur borneInf, Vecteur borneSup, int nombreDimension)
{
    this->nombreParticules = nombreParticules;
    this->borneInf = borneInf;
    this->borneSup = borneSup;
    this->nombreDimension = nombreDimension;
    for (int i = 0; i < nombreParticules; i++)
    {
        this->particules.push_back(creerParticule(borneInf, borneSup, nombreDimension, i));
    }
}

list<Particule> &Univers::getParticules() { return particules; }

void Univers::stromerVerlet(vector<Vecteur> &fOld, double tEnd, double gammaT)
{
    /* Initialisation des forces */
    initialisationForces();
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
        initialisationForces();
        i = 0;
        for (Particule &particule : particules)
        {
            particule.updateVitesse(gammaT, fOld[i]);
            i++;
        }
    }
}

void Univers::initialisationForces()
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

Particule creerParticule(Vecteur borneInf, Vecteur borneSup, int nombreDimension, int id)
{
    random_device rd;
    mt19937 mt(rd());
    double x = 0, y = 0, z = 0, masse;
    if (nombreDimension < 2)
    {
        uniform_real_distribution<double> dist(borneInf.getX(), borneSup.getX());
        x = dist(mt);
    }
    if (nombreDimension < 3)
    {
        uniform_real_distribution<double> dist(borneInf.getY(), borneSup.getY());
        y = dist(mt);
    }
    if (nombreDimension < 4)
    {
        uniform_real_distribution<double> dist(borneInf.getZ(), borneSup.getZ());
        z = dist(mt);
    }
    uniform_real_distribution<double> dist(0, 1);
    masse = dist(mt);
    return Particule(Vecteur(x, y, z), masse, 0, id);
}