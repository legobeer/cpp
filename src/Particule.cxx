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
void Particule::setPosition(Vecteur position) { this->position = position; }

Vecteur Particule::forceGravitationnelleParticule(Particule particule)
{
    Vecteur direction = position.getDirection(particule.getPosition());
    direction *= masse * particule.getMasse() / pow(position.computeDistance(particule.getPosition()), 3);
    return direction;
}

Vecteur Particule::forceInteractionFaible(double rCut, std::unordered_set<Particule, HashParticule> particules, double epsilon, double sigma)
{
    Vecteur force;
    double r = 0;
    Vecteur tmp;
    for (Particule particule : particules)
    {
        if (id != particule.getId())
        {
            r = position.computeDistance(particule.getPosition());
            if (r < rCut)
                tmp = position.getDirection(particule.getPosition()) * (24 * epsilon * (1 - 2 * pow(sigma / r, 6)) * pow(sigma / r, 6) / pow(r, 2));
            else
            {
                /* La distance entre les deux particules est supérieur à rCut
                on néglige ainsi la force d'interaction faible.*/
                tmp = 0;
            }
            force += tmp;
        }
    }
    return force;
}

void Particule::updatePosition(double deltaT)
{
    position += (force * (0.5 / masse * deltaT) + vitesse) * deltaT;
}

void Particule::updateVitesse(double deltaT, Vecteur fOld)
{
    vitesse += (force + fOld) * (0.5 * deltaT / masse);
}
