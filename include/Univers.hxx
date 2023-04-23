#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <list>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <memory>

class Univers
{
private:
    std::vector<std::shared_ptr<Particule>> particules;
    int nombreParticules;
    Vecteur borneInf;
    Vecteur borneSup;
    int nombreDimension;
    Vecteur lD;
    double rCut;
    double sigma = 1;
    double epsilon = 5;
    std::unordered_map<Vecteur, Cellule, Vecteur::HashVecteur>
        cellules;

public:
    Univers(int, Vecteur, Vecteur, Vecteur, int = 3, double = 0);

    friend std::ostream &operator<<(std::ostream &, const Univers &);

    const std::vector<std::shared_ptr<Particule>> &getParticules() const;
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
