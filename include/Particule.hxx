#pragma once
#include "Vecteur.hxx"
#include <vector>
#include <unordered_set>
#include <memory>
#include "conditionLimite.hxx"
/**
 * Cette classe représente une particule dans le système.
 *
 * @param position : Position de la particule.
 * @param masse : Masse de la particule.
 * @param type : Type de la particule (entier).
 * @param id : Identifiant de la particule.
 * @param vitesse : Vitesse initiale de la particule (par défaut, 0).
 */
class Particule
{
private:
    Vecteur position;
    Vecteur vitesse = Vecteur();
    Vecteur force;
    double masse;
    int type;
    int id;

public:
    Particule(Vecteur, double, int, int, Vecteur);

    bool operator==(const Particule &) const;

    friend std::ostream &operator<<(std::ostream &, const Particule &);

    const Vecteur &getVitesse() const;
    const Vecteur &getPosition() const;
    const Vecteur &getForce() const;
    int getId() const;
    double getMasse() const;
    int getType() const;

    void setForce(const Vecteur &);
    void setPosition(const Vecteur &);
    void setVitesse(const Vecteur &);

    /**
     * Met à jour la position de la particule en fonction du pas de temps donné.
     * Calcule la nouvelle position en utilisant la vitesse à l'instant t + deltaT.
     *
     * @param deltaT : Pas de temps.
     */
    void updatePosition(double deltaT);

    /**
     * Met à jour la vitesse de la particule en fonction du pas de temps donné et de la force à l'instant t.
     * Calcule la nouvelle vitesse en utilisant la force à l'instant t + deltaT.
     *
     * @param deltaT : Pas de temps.
     * @param fOld : Vecteur de force à l'instant t.
     */
    void updateVitesse(double deltaT, Vecteur fOld);

    /**
     * Foncteur de hachage pour la classe Particule.
     */
    struct HashParticule
    {
        size_t operator()(const Particule &particule) const
        {
            return particule.id;
        }
    };

    /**
     * Foncteur de hachage pour les pointeurs de Particule.
     */
    struct HashParticulePtr
    {
        size_t operator()(const std::shared_ptr<Particule> &particule) const
        {
            return particule->id;
        }
    };

    /**
     * Calcule la force d'attraction gravitationnelle qu'exerce notre particule
     * sur l'autre particule spécifiée en paramètre.
     *
     * @param particule : L'autre particule sur laquelle s'applique la force gravitationnelle.
     * @return Vecteur : Le vecteur correspondant à la force d'attraction gravitationnelle
     *                  exercée par notre particule sur l'autre particule.
     */
    Vecteur forceGravitationnelleParticule(const Particule &particule) const;

    /**
     * Calcule la force d'interaction faible que notre particule exerce sur toutes les autres particules présentes
     * dans l'ensemble de particules donné.
     *
     * @param rCut : Rayon à partir duquel la force d'interaction faible est négligée.
     * @param particules : Ensemble de particules.
     * @param epsilon : Constante présente dans la force d'interaction faible (par défaut, 5).
     * @param sigma : Constante présente dans la force d'interaction faible (par défaut, 1).
     * @param G : Champ gravitationnel.
     * @return Vecteur correspondant à la force d'interaction faible que notre particule exerce sur toutes les autres particules.
     */
    Vecteur calculForce(double rCut, const std::unordered_set<std::shared_ptr<Particule>, HashParticulePtr> &particules, double epsilon = 5, double sigma = 1, double G = 0) const;

    /**
     * @brief Gère les conditions limites pour une particule donnée.
     *
     * Cette fonction gère les conditions limites pour une particule en fonction des bornes, de la dimension, de la condition limite,
     * de l'epsilon et du sigma donnés. Elle effectue les vérifications nécessaires et applique les actions appropriées en fonction
     * de la condition limite spécifiée.
     *
     * @param borneInf La borne inférieure pour les coordonnées de la particule.
     * @param borneSup La borne supérieure pour les coordonnées de la particule.
     * @param nombreDimension Le nombre de dimensions de l'espace.
     * @param conditionLimite La condition limite à appliquer.
     * @param epsilon La valeur d'epsilon.
     * @param sigma La valeur de sigma.
     *
     * @return Retourne `true` si la particule est absorbée (dans le cas de la condition limite d'absorption), sinon retourne `false`.
     *         Pour les autres conditions limites, la fonction effectue les actions nécessaires et ne renvoie pas de valeur spécifique.
     *
     * @throws InvalidBorneException Si les bornes supérieure et inférieure sont incorrectes.
     */
    bool conditionLimiteManager(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, ConditionLimite conditionLimite, double epsilon = 5, double sigma = 1);

    /**
     * @brief Gère les conditions limites de réflexion pour une particule donnée.
     *
     * Cette fonction gère les conditions limites de réflexion pour une particule en fonction des bornes, de la dimension, de l'epsilon
     * et du sigma donnés. Elle effectue les vérifications nécessaires et ajuste la force appliquée à la particule en cas de
     * proximité avec les limites. Les forces de réflexion sont calculées à l'aide de l'interaction de Lennard-Jones.
     *
     * @param borneInf La borne inférieure pour les coordonnées de la particule.
     * @param borneSup La borne supérieure pour les coordonnées de la particule.
     * @param nombreDimension Le nombre de dimensions de l'espace.
     * @param epsilon La valeur d'epsilon.
     * @param sigma La valeur de sigma.
     *
     * @throws InvalidBorneException Si les bornes supérieure et inférieure sont incorrectes.
     */
    void conditionLimiteReflexion(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, double epsilon, double sigma);

    /**
     * @brief Vérifie la validité d'une particule par rapport aux bornes, dimensions et paramètres.
     *
     * Cette fonction vérifie si une particule est valide en termes de bornes, dimensions et paramètres.
     * Elle lève des exceptions appropriées en cas de problèmes détectés.
     *
     * @param borneInf La borne inférieure pour les coordonnées de la particule.
     * @param borneSup La borne supérieure pour les coordonnées de la particule.
     * @param nombreDimension Le nombre de dimensions de l'espace.
     *
     * @throws InvalidBorneException Si les bornes supérieure et inférieure sont incorrectes.
     * @throws ProblemeVecteurDimension Si les vecteurs de position, vitesse et force ont des composantes non nulles inappropriées pour la dimension de l'espace.
     * @throws ParametrePositifStrictement Si la masse de la particule n'est pas strictement positive.
     * @throws InvalidPositionParticule Si la position de la particule n'est pas valide par rapport aux bornes.
     */
    void invalidParticule(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension) const;
};