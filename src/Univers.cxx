#include "Univers.hxx"
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <vector>
#include <list>
#include <iostream>
#include <bits/stdc++.h>
#include <random>

Univers::Univers(int nombreParticules, Vecteur borneInf, Vecteur borneSup, int nombreDimension)
{
    this->nombreParticules = nombreParticules;
    this->borneInf = borneInf;
    this->borneSup = borneSup;
    this->nombreDimension = nombreDimension;
    this->lD = borneSup - borneInf;
    this->rCut = 0;
    for (int i = 0; i < nombreParticules; i++)
    {
        /* TODO constructor */
        this->particules.push_back(creerParticule(borneInf, borneSup, nombreDimension, i));
    }
}

Univers::Univers(int nombreParticules, Vecteur borneInf, Vecteur borneSup, int nombreDimension, double rCut)
{
    this->nombreParticules = nombreParticules;
    this->borneInf = borneInf;
    this->borneSup = borneSup;
    this->nombreDimension = nombreDimension;
    this->lD = borneSup - borneInf;
    this->rCut = rCut;
    for (int i = 0; i < nombreParticules; i++)
    {
        this->particules.push_back(creerParticule(borneInf, borneSup, nombreDimension, i));
    }
    if (rCut == 0)
        return;
    creerCellules();
}
std::ostream &operator<<(std::ostream &, const Univers &u)
{
    for (Particule particule : u.particules)
        std::cout << particule << std::endl;
    return std::cout;
}

/* Constructor used for make the test of Stromer-Verlet TP2 */

std::list<Particule> Univers::getParticules() { return particules; }

int Univers::getNombreParticules() { return nombreParticules; }

void Univers::stromerVerlet(std::vector<Vecteur> fOld, double tEnd, double gammaT)
{
    /* Initialisation des forces */
    calculForces();
    double t = 0;
    while (t < tEnd)
    {
        t += gammaT;
        for (Particule &particule : particules)
        {
            particule.updatePosition(gammaT);
            updateMaillage();
            fOld[particule.getId()] = particule.getForce();
            particule.setForce(0);
        }
        /* Calcul des forces */
        calculForces();
        //     /* À décommenter pour afficher une ellipse */
        // for (Particule &particule : particules)
        // {
        //     // if (particule.getId() == 1)
        //     //     cout << particule.getPosition().getX() << " " << particule.getPosition().getY() << endl;
        //     // particule.updateVitesse(gammaT, fOld[particule.getId()]);
        // }
    }
}

void Univers::addParticule(Particule p)
{
    this->particules.push_back(p);
}

void Univers::creerCellules()
{
    Vecteur coordonnees;
    for (Particule &particule : particules)
    {
        coordonnees = particule.getPosition().attributionMaillage(rCut);
        cellules[coordonnees].addParticule(particule);
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
        voisins = coordonnes.getVoisins(nombreDimension);
        for (Vecteur voisin : voisins)
        {
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
    Vecteur coordonnees;
    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        for (Particule particule : p->second.getParticules())
        {
            if (!(p->first == particule.getPosition().attributionMaillage(rCut)))
            {
                /* Il faut changer la position de la particule dans le maillage */
                p->second.deleteParticule(particule);
                /* on ajoute la particule au bon endroit */
                cellules[particule.getPosition().attributionMaillage(rCut)].addParticule(particule);
                /* On vérifie si la liste des particules n'est pas vide */
                if (p->second.getParticules().size() == 0)
                    cellules.erase(p->first);
            }
        }
    }
    /* Maitenant on va mettre à jour les voisins */
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
        for (Particule particule : p->second.getParticules())
        {
            /* Force avec les particules dans la même maille */
            force = 0;
            force += particule.forceInteractionFaible(rCut, p->second.getParticules(), epsilon, sigma);
            for (Vecteur voisin : p->second.getCellulesVoisines())
            {
                force += particule.forceInteractionFaible(rCut, cellules[voisin].getParticules(), epsilon, sigma);
            }
            /* Mis à jour de la force d'interaction faible */
            particule.setForce(particule.getForce() + force);
        }
    }
}

void Univers::calculForcesGravitationnelles()
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
            Fij = particuleI.forceGravitationnelleParticule(particuleJ);
            particuleI.setForce(particuleI.getForce() + Fij);
            particuleJ.setForce(particuleJ.getForce() - Fij);
            jiemeParticule++;
        }
        iemeParticule++;
    }
}

Particule creerParticule(Vecteur borneInf, Vecteur borneSup, int nombreDimension, int id)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    double x = 0, y = 0, z = 0, masse;
    if (nombreDimension > 0)
    {
        std::uniform_real_distribution<double> dist(borneInf.getX(), borneSup.getX());
        x = dist(mt);
        std::cout << x << std::endl;
    }
    if (nombreDimension > 1)
    {
        std::uniform_real_distribution<double> dist(borneInf.getY(), borneSup.getY());
        y = dist(mt);
        std::cout << y << std::endl;
    }
    if (nombreDimension > 2)
    {
        std::uniform_real_distribution<double> dist(borneInf.getZ(), borneSup.getZ());
        z = dist(mt);
        std::cout << z << std::endl;
    }
    std::uniform_real_distribution<double> dist(0.005, 0.01);
    masse = dist(mt);
    return Particule(Vecteur(x, y, z), masse, 0, id);
}
