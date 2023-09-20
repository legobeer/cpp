#pragma once
#include <unordered_set>
#include "Particule.hxx"
/**
 * Cette classe est utilisée dans la classe Univers où elle représente une cellule du maillage.
 * Chaque cellule contient un ensemble de particules et un ensemble de cellules voisines.
 *
 * @param particules : Ensemble de particules présentes dans la cellule.
 * @param cellulesVoisines : Ensemble des cellules voisines contenant des particules.
 * @param id : Identifiant de la cellule.
 */
class Cellule
{
public:
    /**
     * Fonction de hachage pour les pointeurs de Cellule.
     * Utilisé dans les structures de données basées sur le hachage, comme une table de hachage.
     */
    struct HashCellulePtr
    {
        size_t operator()(const std::shared_ptr<Cellule> &cellule) const
        {
            return cellule->id;
        }
    };

private:
    std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> particules;
    std::unordered_set<std::shared_ptr<Cellule>, Cellule::HashCellulePtr> cellulesVoisines;
    int id;
    std::vector<Vecteur> voisins;

public:
    /**
     * Constructeur de la classe Cellule.
     *
     * @param id : Identifiant de la cellule.
     * @param position : Position de notre cellule dans le maillage
     * @param dimension : Dimension de notre espace
     */
    Cellule(int id, const Vecteur &position, int dimension);

    /**
     * Opérateur d'égalité pour comparer deux cellules.
     *
     * @param otherCellule : Autre cellule à comparer.
     * @return true si les cellules sont égales, false sinon.
     */
    bool operator==(const Cellule &otherCellule) const;

    /**
     * Récupère l'ensemble des particules présentes dans la cellule.
     *
     * @return Référence constante vers l'ensemble des particules.
     */
    const std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> &getParticules() const;

    /**
     * Récupère l'ensemble des cellules voisines contenant des particules.
     *
     * @return Référence constante vers l'ensemble des cellules voisines.
     */
    const std::unordered_set<std::shared_ptr<Cellule>, Cellule::HashCellulePtr> &getCellulesVoisines() const;

    /**
     * Récupère l'ensemble des cases voisines contenant des particules.
     * Attention les cases comprennent des cellules vides.
     *
     * @return Référence constante vers l'ensemble des voisins.
     */
    const std::vector<Vecteur> &getVoisins() const;

    /**
     * Ajoute une particule à l'ensemble des particules de la cellule.
     *
     * @param particule : Pointeur vers la particule à ajouter.
     */
    void addParticule(std::shared_ptr<Particule> particule);

    /**
     * Insère les coordonnées d'une cellule voisine dans l'ensemble des cellules voisines de la cellule courante.
     *
     * @param cellule : Pointeur vers la cellule voisine à ajouter.
     */
    void addCelluleVoisine(std::shared_ptr<Cellule> cellule);

    /**
     * Supprime une particule de l'ensemble des particules de la cellule.
     *
     * @param particule : Pointeur vers la particule à supprimer.
     */
    void deleteParticule(std::shared_ptr<Particule> particule);

    /**
     * Supprime une cellule voisine de l'ensemble des cellules voisines de la cellule courante.
     *
     * @param cellule : Pointeur vers la cellule voisine à supprimer.
     */
    void deleteVoisin(std::shared_ptr<Cellule> cellule);
};
