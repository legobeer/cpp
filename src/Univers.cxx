#include "Univers.hxx"
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <vector>
#include <list>
#include <iostream>
#include <bits/stdc++.h>
#include <random>

Univers::Univers(int nombreParticules, Vecteur borneInf, Vecteur borneSup, Vecteur lD, int nombreDimension, double rCut)
{
    this->nombreParticules = nombreParticules;
    this->borneInf = borneInf;
    this->borneSup = borneSup;
    this->nombreDimension = nombreDimension;
    this->lD = lD;
    this->rCut = 0;
    for (int i = 0; i < nombreParticules; i++)
    {
        /* TODO constructor */
        this->particules.emplace_back(std::make_shared<Particule>(creerParticule(borneInf, borneSup, nombreDimension, i)));
    }
    if (rCut == 0)
        return;

    creerCellules();
}

std::ostream &operator<<(std::ostream &, const Univers &u)
{
    for (auto it = u.particules.begin(); it != u.particules.end(); ++it)
        std::cout << **it;
    return std::cout;
}

/* Constructor used for make the test of Stromer-Verlet TP2 */

const std::vector<std::shared_ptr<Particule>> &Univers::getParticules() const { return particules; }

int Univers::getNombreParticules() { return nombreParticules; }

std::unordered_map<Vecteur, Cellule, Vecteur::HashVecteur> Univers::getCellules() { return cellules; }

void Univers::stromerVerlet(std::vector<Vecteur> fOld, double tEnd, double deltaT)
{
    /* Initialisation des forces */
    if (deltaT == 0)
        return;
    calculForces();
    double t = 0;

    while (t < tEnd)
    {
        t += deltaT;
        for (const auto &particule : particules)
        {
            /* Mis à jour de la position de notre particule à l'instant t + deltaT */
            particule->updatePosition(deltaT);
            updateMaillage();
            fOld[particule->getId()] = particule->getForce();
            /* Mis à 0 de la force de la particule */
            particule->setForce(0);
        }
        /* Calcul des forces à l'instant t + deltaT */
        calculForces();
        for (const auto &particule : particules)
        {
            /* À décommenter pour afficher une ellipse */
            // if (particule->getId() == 3)
            // std::cout << particule->getPosition().getX() << " " << particule->getPosition().getY() << std::endl;
            particule->updateVitesse(deltaT, fOld[particule->getId()]);
        }
    }
}

void Univers::addParticule(Particule p)
{

    this->nombreParticules += 1;
    this->particules.emplace_back(std::make_shared<Particule>(p));
}

void Univers::creerCellules()
{

    for (const auto &particule : particules)
    {
        cellules[particule->getPosition().attributionMaillage(rCut)].addParticule(particule);
    }
    /* We have to compute all the neighboors */
    creerVoisinsCellules();
}

void Univers::creerVoisinsCellules()
{
    std::vector<Vecteur> voisins;
    Vecteur coordonnes;
    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        coordonnes = p->first;
        for (Vecteur voisin : coordonnes.getVoisins(nombreDimension))
        {
            /* On vérifie si la case voisin contient des particules */
            if (cellules.find(voisin) != cellules.end())
                cellules[coordonnes].addCelluleVoisine(voisin);
        }
    }
}

void Univers::calculForces()
{
    calculForcesGravitationnelles();
    calculForcesInteractionsFaibles();
}

void Univers::updateMaillage()
{
    updateMaillageParticules();
    /* Maitenant on va mettre à jour les voisins */
    updateMaillageVoisins();
}

void Univers::updateMaillageParticules()
{
    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        for (const auto &particule : p->second.getParticules())
        {
            if (!(p->first == particule->getPosition().attributionMaillage(rCut)))
            {
                /* Il faut changer la position de la particule dans le maillage */
                p->second.deleteParticule(particule);
                /* on ajoute la particule au bon endroit */
                cellules[particule->getPosition().attributionMaillage(rCut)].addParticule(particule);
                /* On vérifie si la liste des particules n'est pas vide */
                if (p->second.getParticules().size() == 0)
                    cellules.erase(p->first);
            }
        }
    }
}

void Univers::updateMaillageVoisins()
{
    std::vector<Vecteur> voisinsPossibles;
    Vecteur tmp;
    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        tmp = p->first;
        voisinsPossibles = tmp.getVoisins(nombreDimension);
        for (Vecteur voisinPotentiel : voisinsPossibles)
        {
            if (cellules.find(voisinPotentiel) != cellules.end() && !(p->second.getCellulesVoisines().find(voisinPotentiel) != p->second.getCellulesVoisines().end()))
                p->second.addCelluleVoisine(voisinPotentiel);
            else if (p->second.getCellulesVoisines().find(voisinPotentiel) != p->second.getCellulesVoisines().end() && !(cellules.find(voisinPotentiel) != cellules.end()))
                p->second.deleteVoisin(voisinPotentiel);
        }
    }
}

void Univers::calculForcesInteractionsFaibles()
{
    Vecteur coordonnees;
    Vecteur force;
    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        for (const auto &particule : p->second.getParticules())
        {
            /* Force avec les particules dans la même maille */
            force = 0;
            force += particule->forceInteractionFaible(rCut, p->second.getParticules(), epsilon, sigma);
            for (Vecteur voisin : p->second.getCellulesVoisines())
            {
                force += particule->forceInteractionFaible(rCut, cellules[voisin].getParticules(), epsilon, sigma);
            }
            /* Mis à jour de la force d'interaction faible */
            particule->setForce(particule->getForce() + force);
        }
    }
}

void Univers::calculForcesGravitationnelles()
{
    Vecteur Fij;

    for (int i = 0; i < nombreParticules; i++)
    {
        Particule &particuleI = *particules[i];
        for (int j = i + 1; j < nombreParticules; j++)
        {

            Particule &particuleJ = *particules[j];
            Fij = particuleI.forceGravitationnelleParticule(particuleJ);
            particuleI.setForce(particuleI.getForce() + Fij);
            particuleJ.setForce(particuleJ.getForce() - Fij);
        }
    }
}

Particule creerParticule(Vecteur borneInf, Vecteur borneSup, int nombreDimension, int id)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.005, 0.01);
    double masse = dist(mt);
    return Particule(randomVecteur(nombreDimension, borneInf, borneSup), masse, 0, id);
}
