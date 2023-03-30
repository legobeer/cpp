#pragma once
#include "Vecteur.hxx"
#include <list>
#include <vector>
#include <unordered_set>

class Particule
{
private:
    Vecteur position;
    Vecteur vitesse;
    Vecteur force;
    double masse;
    int type;
    int id;

public:
    Particule(Vecteur, double, int, int, Vecteur = 0);

    bool operator==(const Particule &) const;

    friend std::ostream &operator<<(std::ostream &, const Particule &);

    Vecteur getVitesse();
    Vecteur getPosition();
    Vecteur getForce();
    int getId();
    double getMasse();

    void setForce(Vecteur force);

    void updatePosition(double);

    void updateVitesse(double, Vecteur);

    struct HashParticule
    {
        size_t operator()(const Particule &particule) const
        {
            return particule.id;
        }
    };

    Vecteur forceInteractionFaible(double rCut, std::unordered_set<Particule, HashParticule> particules, double epsilon = 5, double sigma = 1);

    Vecteur forceGravitationnelleParticule(Particule);
};