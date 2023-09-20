#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
/**
 * La classe Vecteur permet de créer un vecteur en dimension
 * permettant de faire des opérations élémentaires sur les vecteurs
 * similaires à celles disponibles dans la bibliothèque numpy en Python.
 *
 * @param x : Composante x du vecteur.
 * @param y : Composante y du vecteur.
 * @param z : Composante z du vecteur.
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

    double getX() const;

    double getY() const;

    double getZ() const;

    void setX(double);

    void setY(double);

    void setZ(double);

    void setVecteur(const Vecteur &);

    /**
     * Cette fonction permet de donner la maille
     * du vecteur en fonction d'un paramètre correspondant
     * à la taille de la maille.
     *
     * @param rCut : Taille de la maille.
     * @return Vecteur : Coordonnées de la maille.
     */
    Vecteur attributionMaillage(double) const;

    /**
     * Cette fonction permet de connaître tous les voisins de Moore d'une case
     * c'est pourquoi cette méthode est utilisable uniquement si tous les
     * attributs du vecteur sont des entiers.
     *
     * @param nombreDimension : Dimension de notre espace. Peut varier entre 1 et 3.
     * @return std::vector<Vecteur> : Tableau de vecteurs contenant tous les voisins
     *                                de Moore de notre vecteur dans un espace de dimension
     *                                `nombreDimension`.
     */
    std::vector<Vecteur> getVoisins(int) const;

    /**
     * Calcule la distance au carré entre 2 points.
     *
     * @param point : Point avec lequel on veut calculer la distance.
     * @return double : Distance entre notre premier point et le second point en paramètre.
     */
    double computeDistance2(const Vecteur &point) const;

    /**
     * Cette méthode permet de renvoyer le vecteur entre 2 points :
     * notre point et le point en paramètre.
     *
     * @param vecteur : Point.
     * @return Vecteur : Vecteur entre nos 2 points.
     */
    Vecteur getDirection(const Vecteur &) const;

    /**
     * Hash de notre classe Vecteur. On utilise le code ASCII ainsi
     * que la conversion de nos paramètres en chaîne de caractères
     * pour définir le hash de notre classe.
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

/**
 * @brief Vérifie la validité d'un nombre de dimensions.
 *
 * Cette fonction vérifie la validité d'un nombre de dimensions. Elle génère une exception si le nombre de dimensions spécifié
 * est invalide.
 *
 * @param nombreDimension Le nombre de dimensions à vérifier.
 *
 * @throws DimensionInvalide Si le nombre de dimensions spécifié est invalide.
 */
void dimensionInvalide(int nombreDimension);

/**
 * @brief Vérifie la validité d'un vecteur dans un certain nombre de dimensions.
 *
 * Cette fonction vérifie la validité d'un vecteur dans un certain nombre de dimensions. Elle effectue les vérifications nécessaires
 * et génère des exceptions appropriées en cas d'invalidité.
 *
 * @param nombreDimension Le nombre de dimensions du vecteur.
 * @param vecteur Le vecteur à vérifier.
 *
 * @throws DimensionInvalide Si le nombre de dimensions spécifié est invalide.
 * @throws ProblemeVecteurDimension Si le vecteur ne correspond pas au nombre de dimensions spécifié.
 */
void vecteurInvalide(int nombreDimension, const Vecteur &vecteur);

/**
 * @brief Vérifie la validité des bornes spécifiées pour un vecteur dans un certain nombre de dimensions.
 *
 * Cette fonction vérifie la validité des bornes spécifiées pour un vecteur dans un certain nombre de dimensions. Elle effectue
 * les vérifications nécessaires et génère des exceptions appropriées en cas d'invalidité.
 *
 * @param borneInf La borne inférieure pour les coordonnées du vecteur.
 * @param borneSup La borne supérieure pour les coordonnées du vecteur.
 * @param nombreDimension Le nombre de dimensions du vecteur.
 *
 * @throws DimensionInvalide Si le nombre de dimensions spécifié est invalide.
 * @throws ProblemeVecteurDimension Si les bornes inférieure et supérieure ne correspondent pas au nombre de dimensions spécifié.
 * @throws InvalidBorneException Si les bornes spécifiées sont invalides.
 */
void invalidBorne(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension);

/**
 * @brief Génère un vecteur aléatoire dans les limites spécifiées.
 *
 * Cette fonction génère un vecteur aléatoire dans les bornes spécifiées pour un certain nombre de dimensions.
 *
 * @param nombreDimension Le nombre de dimensions du vecteur.
 * @param borneInf La borne inférieure pour les coordonnées du vecteur.
 * @param borneSup La borne supérieure pour les coordonnées du vecteur.
 *
 * @return Retourne un vecteur aléatoire généré dans les bornes spécifiées.
 */
Vecteur randomVecteur(int nombreDimension, const Vecteur &borneInf, const Vecteur &borneSup);
