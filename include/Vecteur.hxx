#pragma once
#include <list>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

/**
 * La classe Vecteur permet de créer un vecteur en dimension
 * permettant de faire des opérations élémentaires sur les vecteurs
 * que l'on peut avoir dans numpy en python.
 *
 * @param x
 * @param y
 * @param z
 */
class Vecteur
{
private:
    double x;
    double y;
    double z;

public:
    Vecteur(double = 0, double = 0, double = 0);

    Vecteur operator+(const Vecteur &);

    Vecteur &operator+=(const Vecteur &);

    Vecteur operator-() const;

    Vecteur operator-(const Vecteur &);

    Vecteur &operator*=(double);

    Vecteur operator*(double);

    Vecteur &operator*=(const Vecteur &);

    Vecteur &operator-=(const Vecteur &);

    Vecteur &operator=(double);

    bool operator==(const Vecteur &otherVecteur) const;

    friend std::ostream &operator<<(std::ostream &, const Vecteur &);

    double getX();

    double getY();

    double getZ();

    void setXInt(int);

    void setYInt(int);

    void setZInt(int);

    void setVecteur(Vecteur);

    /**
     * Cette fonction permet de donner la maille
     * du vecteur en fonction d'un paramètre correspondant
     * à la taille de la maille.
     *
     * @param rCut taille de la maille.
     *
     * @return Vecteur coordonnées de la maille.
     */
    Vecteur attributionMaillage(double);

    /**
     * Cette fonction permet de connaître tous les voisins de Moore d'une case
     * c'est pourquoi cette méthode est utilisable uniquement si tous les
     * attributs du vecteurs sont des entiers.
     *
     * @param nombreDimension correspond à la dimension de notre espace. Peut varier
     * entre 1 et 3.
     *
     * @return Un tableau de vecteur contenant tous les voisins de Moore de notre vecteur
     * dans un espace de dimension : nombreDimension.
     */
    std::vector<Vecteur> getVoisins(int);

    /**
     * Calcule la distance entre 2 points.
     *
     * @param point point avec lequel on veut calculer la distance.
     * @return la distance entre notre premier point et le second point
     * en paramètre.
     */
    double computeDistance(Vecteur);

    /**
     * Cette méthode permet de renvoyer le vecteur entre 2 points :
     * notre point et le point en paramètre.
     *
     * @param point
     * @return Vecteur entre nos 2 points.
     */
    Vecteur getDirection(Vecteur);

    /**
     * Hash de notre classe vecteur. On utilise le code ASCII ainsi
     * que la conversion de nos paramètres en chaîne de caractère
     * pour définir le hash de notre classe.
     *
     */
    struct HashVecteur
    {
        size_t operator()(const Vecteur &vecteur) const
        {
            std::string tmp = std::to_string(vecteur.x) + "," + std::to_string(vecteur.y) + "," + std::to_string(vecteur.z);

            int hashCode = 0;
            for (size_t i = 0; i < tmp.length(); i++)
            {
                hashCode += tmp[i] * pow(31, i);
            }
            return hashCode;
        }
    };
};

Vecteur randomVecteur(int, Vecteur, Vecteur);
