#include <list>
#include <vector>
#include <bits/stdc++.h>
#include "Vecteur.hxx"
#include "Particule.hxx"
#include <iostream>

Particule::Particule(Vecteur position, double masse, int type, int id, Vecteur vitesse)
{
    this->position = position;
    this->vitesse = vitesse;
    this->force = Vecteur(0, 0, 0);
    this->masse = masse;
    this->type = type;
    this->id = id;
}

bool Particule::operator==(const Particule &otherParticule) const
{
    if (this->id == otherParticule.id)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &os, const Particule &p)
{
    std::cout << "Particule n°" << p.id << "\nPosition : " << p.position << std::endl;
    std::cout << "Masse : " << p.masse << "\nType : " << p.type << "\nVitesse : " << p.vitesse << std::endl;
    std::cout << "Force : " << p.force << std::endl;
    std::cout << "------------------------------------";
    return os;
}

Vecteur Particule::getVitesse() { return vitesse; }
Vecteur Particule::getPosition() { return position; }
Vecteur Particule::getForce() { return force; }
int Particule::getId() { return id; }
double Particule::getMasse() { return masse; }
int Particule::getType() { return type; }

void Particule::setForce(Vecteur force) { this->force = force; }

Vecteur Particule::forceGravitationnelleParticule(Particule particule)
{
    Vecteur direction = position.getDirection(particule.getPosition());
    direction *= masse * particule.getMasse() / pow(position.computeDistance(particule.getPosition()), 3);
    return direction;
}

Vecteur Particule::forceInteractionFaible(double rCut, std::unordered_set<Particule, HashParticule> particules, double epsilon, double sigma)
{
    Vecteur force = 0;
    double r = 0;
    Vecteur tmp = 0;
    for (Particule particule : particules)
    {
        if (id != particule.getId())
        {
            r = position.computeDistance(particule.getPosition());
            if (r < rCut)
                tmp = position.getDirection(particule.getPosition()) * (24 * epsilon * (1 - 2 * pow(sigma / r, 6)) * pow(sigma / r, 6) / pow(r, 2));
            else
                tmp = 0;
            force += tmp;
        }
    }
    return force;
}

void Particule::updatePosition(double gammaT)
{
    Vecteur fParticule = force;
    fParticule *= 0.5 / masse * gammaT;
    fParticule += vitesse;
    fParticule *= gammaT;
    position += fParticule;
}

void Particule::updateVitesse(double gammaT, Vecteur fOld)
{
    Vecteur fParticule = force;
    fParticule += fOld;
    fParticule *= 0.5 * gammaT / masse;
    vitesse += fParticule;
}
