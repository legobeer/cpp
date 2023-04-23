#pragma once
#include "Vecteur.hxx"
#include <list>
#include <vector>
#include <unordered_set>
#include <memory>

/**
 * Cette classe a pour but de décrire une particule.
 *
 * @param position correspond à la position de la particule.
 * @param vitesse correspond à la vitesse de la particule.
 * @param force correspond à la force de la particule.
 * @param masse correspond à la masse de la particule.
 * @param type correspond au type de particule (int).
 * @param id est l'id de la particule. Il nous sert à savoir que deux particules
 * sont bien différentes. Il est utilisé pour définir le hash de la particule.
 *
 */
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
    int getId() const;
    double getMasse() const;
    int getType() const;

    void setForce(Vecteur);
    void setPosition(Vecteur);

    /**
     * Cette fonction met à jour la position de la particule.
     * On calcule la vitesse à l'instant t + deltaT.
     *
     * @param deltaT pas du temps.
     */
    void updatePosition(double);

    /**
     * Cette fonction met à jour la vitesse de la particule.
     * On calcule la vitesse à l'instant t + deltaT.
     *
     * @param deltaT pas du temps.
     * @param fOld vecteur force à l'instant t.
     */
    void updateVitesse(double, Vecteur);

    /**
     * Définition du hash pour notre classe particule.
     */
    struct HashParticule
    {
        size_t operator()(const Particule &particule) const
        {
            return particule.id;
        }
    };

    struct HashParticulePtr
    {
        size_t operator()(const std::shared_ptr<Particule> &particule) const
        {
            return particule->id;
        }
    };

    /**
     * Calcule la force d'interaction faible que notre particule exerce
     * sur toutes les autres particules présentes dans le set particules.
     *
     * @param rCut rayon à partir duquel la force d'interaction faible est négligée.
     * @param particules ensemble de particules.
     * @param epsilon constante présente dans la force d'interaction faible.
     * @param sigma constante présente dans la force d'interaction faible.
     * @return Vecteur correspondant à la force d'interaction faible que notre particule
     * exerce sur toutes les autres particules présentes dans le set particules.
     */
    Vecteur forceInteractionFaible(double, std::unordered_set<std::shared_ptr<Particule>, HashParticulePtr>, double = 5, double = 1);

    /**
     * Calcule de la force d'attraction gravitationnelle
     * qu'exerce notre particule sur l'autre particule.
     *
     * @param particule autre particule.
     * @return Vecteur correspondant à la force d'interaction gravitationnelle que notre
     * particule exerce sur l'autre particule.
     */
    Vecteur forceGravitationnelleParticule(Particule);
};