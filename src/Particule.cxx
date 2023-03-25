#include "Vecteur.hxx"
#include <list>
#include <vector>
using namespace std;

class Particule
{
private:
    Vecteur position;
    Vecteur vitesse;
    Vecteur force;
    double masse;
    int type;
    int id;

    Particule(Vecteur position, Vecteur vitesse, double masse, int type, int id)
    {
        this->position = position;
        this->vitesse = vitesse;
        this->force = Vecteur(0, 0, 0);
        this->masse = masse;
        this->type = type;
        this->id = id;
    }
    Vecteur &getVitesse() { return vitesse; }
    Vecteur &getPosition() { return position; }
    Vecteur &getForce() { return force; }
    double getMasse() { return masse; }
    void computeForce(list<Particule> &particules)
    {
        for (Particule &particule : particules)
        {
            if (&particule == this)
                continue;
        }
    }
};

void stromerVerlet(list<Particule> &particules, vector<Vecteur> &fOld)
{
}