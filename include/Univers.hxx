#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <vector>
#include <list>
#include <unordered_map>
#include <bits/stdc++.h>

class Univers
{
private:
    list<Particule> particules;
    int nombreParticules;
    Vecteur borneInf;
    Vecteur borneSup;
    int nombreDimension;
    Vecteur lD;
    double rCut;
    unordered_map<int, Cellule> cellules;

public:
    Univers(int, Vecteur, Vecteur, int);

    Univers(int, Vecteur, Vecteur, int, double);

    list<Particule> getParticules();

    int getNombreParticules();

    void creerCellules();

    void creerVoisinsCellules();

    void addParticule(Particule);

    void stromerVerlet(vector<Vecteur>, double, double);

    void initialisationForces();

    void display();
};

Particule creerParticule(Vecteur, Vecteur, int, int);
