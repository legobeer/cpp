#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <list>
#include <unordered_map>
#include <bits/stdc++.h>

class Univers
{
private:
    std::list<Particule> particules;
    int nombreParticules;
    Vecteur borneInf;
    Vecteur borneSup;
    int nombreDimension;
    Vecteur lD;
    double rCut;
    double sigma;
    double epsilon;
    std::unordered_map<Vecteur, Cellule, Vecteur::HashVecteur>
        cellules;

public:
    Univers(int, Vecteur, Vecteur, int = 3, double = 0);

    friend std::ostream &operator<<(std::ostream &, const Univers &);

    std::list<Particule> getParticules();
    int getNombreParticules();
    std::unordered_map<Vecteur, Cellule, Vecteur::HashVecteur> getCellules();

    void creerCellules();

    void creerVoisinsCellules();

    void updateMaillage();

    void updateMaillageParticules();

    void updateMaillageVoisins();

    void addParticule(Particule);

    void stromerVerlet(std::vector<Vecteur>, double, double);

    void calculForcesGravitationnelles();

    void calculForces();

    void calculForcesInteractionsFaibles();
};

Particule creerParticule(Vecteur, Vecteur, int, int);
