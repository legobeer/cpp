#pragma once
#include <unordered_set>
#include "Particule.hxx"
#include "Vecteur.hxx"

/**
 * Cette classe est utilisé dans la classe Univers où elle est utilisée
 * comme valeur d'une table de hachage. Sa clé associée correspond à la case du
 * maillage.
 *
 * @param particules : regroupe toutes les particules présentes dans une maille.
 * @param cellulesVoisines : regroupe toutes les mailles voisines contenant des particules.
 *
 */
class Cellule
{
private:
    std::unordered_set<Particule, Particule::HashParticule> particules;
    std::unordered_set<Vecteur, Vecteur::HashVecteur> cellulesVoisines;

public:
    std::unordered_set<Particule, Particule::HashParticule> getParticules();

    std::unordered_set<Vecteur, Vecteur::HashVecteur> getCellulesVoisines();

    /**
     * Cette fonction insère la particule en paramètre dans le set particules
     * de la classe Cellule
     *
     * @param particule
     */
    void addParticule(Particule);

    /**
     * Cette fonction insère les coordonnées d'un vecteur au sein
     * du set stockant toutes les cases voisines où des particules sont
     * présentes.
     *
     * @param vecteur coordonnées d'une case voisine où
     * des particules sont présentes
     */
    void addCelluleVoisine(Vecteur);

    /**
     * Cette fonction supprimela particule en paramètre du set particules
     * de la classe Cellule.
     *
     * @param particule
     */
    void deleteParticule(Particule);

    /**
     * Cette fonction suppriment la case voisine prise en
     * paramètre du set stockant toutes les cases voisines.
     *
     * @param vecteur coordonnées d'une case voisine où
     * des particules sont présentes.
     */
    void deleteVoisin(Vecteur);
};
