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
    this->lD = 0;
    this->rCut = 0;
    for (int i = 0; i < nombreParticules; i++)
    {
        this->particules.push_back(creerParticule(borneInf, borneSup, nombreDimension, i));
    }
}

Univers::Univers(int nombreParticules, Vecteur borneInf, Vecteur borneSup, int nombreDimension, double lD, double rCut)
{
    this->nombreParticules = nombreParticules;
    this->borneInf = borneInf;
    this->borneSup = borneSup;
    this->nombreDimension = nombreDimension;
    this->lD = lD;
    this->rCut = rCut;
    for (int i = 0; i < nombreParticules; i++)
    {
        this->particules.push_back(creerParticule(borneInf, borneSup, nombreDimension, i));
    }
}

/* Constructor used for make the test of Stromer-Verlet TP2 */

list<Particule> Univers::getParticules() { return particules; }

int Univers::getNombreParticules() { return nombreParticules; }

void Univers::stromerVerlet(vector<Vecteur> fOld, double tEnd, double gammaT)
{
    /* Initialisation des forces */
    initialisationForces();
    double t = 0;
    while (t < tEnd)
    {
        t += gammaT;
        for (Particule &particule : particules)
        {
            particule.updatePosition(gammaT);
            fOld[particule.getId()] = *particule.getForce();
            *particule.getForce() = Vecteur();
        }
        /* Calcul des forces */
        initialisationForces();
        for (Particule &particule : particules)
        {
            if (particule.getId() == 2)
            {
                cout << particule.getPosition().getX() << " " << particule.getPosition().getY() << endl;
            }
            particule.updateVitesse(gammaT, fOld[particule.getId()]);
        }
    }
}

void Univers::addParticule(Particule p)
{
    this->particules.push_back(p);
}

// void Univers::creerCellules()
// {
//     Vecteur coordonnees;
//     for (Particule &particule : particules)
//     {
//         coordonnees = particule.getPosition().attributionMaillage(rCut);
//         /* Check if the key is in the map */
//         cellules[coordonnees].addParticule(particule);
//     }
//     /* We have to compute all the neighboors */
// }

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
            {
                jiemeParticule++;
                continue;
            }
            Fij = particuleI.forceParticule(particuleJ);
            particuleI.getForce()->addVectors(Fij);
            Fij.multiplyScalar(-1);
            particuleJ.getForce()->addVectors(Fij);
            jiemeParticule++;
        }
        iemeParticule++;
    }
}

void Univers::display()
{
    for (Particule particule : particules)
        particule.display();
}

Particule creerParticule(Vecteur borneInf, Vecteur borneSup, int nombreDimension, int id)
{
    random_device rd;
    mt19937 mt(rd());
    double x = 0, y = 0, z = 0, masse;
    if (nombreDimension > 0)
    {
        uniform_real_distribution<double> dist(borneInf.getX(), borneSup.getX());
        x = dist(mt);
        cout << x << endl;
    }
    if (nombreDimension > 1)
    {
        uniform_real_distribution<double> dist(borneInf.getY(), borneSup.getY());
        y = dist(mt);
        cout << y << endl;
    }
    if (nombreDimension > 2)
    {
        uniform_real_distribution<double> dist(borneInf.getZ(), borneSup.getZ());
        z = dist(mt);
        cout << z << endl;
    }
    uniform_real_distribution<double> dist(0.005, 0.01);
    masse = dist(mt);
    return Particule(Vecteur(x, y, z), masse, 0, id);
}