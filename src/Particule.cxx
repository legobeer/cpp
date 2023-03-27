#include <list>
#include <vector>
#include <bits/stdc++.h>
#include "Vecteur.hxx"
#include "Particule.hxx"
#include <iostream>

using namespace std;

Particule::Particule(Vecteur position, double masse, int type, int id)
{
    this->position = position;
    this->vitesse = Vecteur(0, 0, 0);
    this->force = Vecteur(0, 0, 0);
    this->masse = masse;
    this->type = type;
    this->id = id;
}

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
    direction.multiplyScalar(1 / pow(position.computeDistance(particule.getPosition()), 3));
    return direction;
}

void Particule::updatePosition(double gammaT)
{
    Vecteur fParticule = force;
    fParticule.multiplyScalar(0.5 / masse * gammaT);
    fParticule.addVectors(vitesse);
    fParticule.multiplyScalar(gammaT);
    position.addVectors(fParticule);
}

void Particule::updateVitesse(double gammaT, Vecteur fOld)
{
    Vecteur fParticule = force;
    fParticule.addVectors(fOld);
    fParticule.multiplyScalar(0.5 * gammaT / masse);
    vitesse.addVectors(fParticule);
}

void Particule::display()
{
    cout << "Particule n°" << id << "\nPosition : ";
    position.displayVector();
    cout << "Masse : " << masse << "\nType : " << type << "\nVitesse : ";
    vitesse.displayVector();
    cout << "Force : ";
    force.displayVector();
    cout << "------------------------------------" << endl;
}
