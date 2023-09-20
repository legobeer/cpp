#pragma once
#include "Vecteur.hxx"
#include "Particule.hxx"
#include "Cellule.hxx"
#include <unordered_map>
#include <vector>
#include <memory>

/**
 * La classe Univers représente l'univers dans lequel évoluent les particules.
 * Elle gère la simulation et le calcul des forces entre les particules.
 *
 * @param particules : Un vecteur contenant des pointeurs partagés vers les particules présentes dans l'univers.
 * @param borneInf : Les coordonnées de la borne inférieure de l'univers.
 * @param borneSup : Les coordonnées de la borne supérieure de l'univers.
 * @param nombreDimension : La dimension de l'espace de l'univers.
 * @param lD : Le vecteur contenant les dimensions de la maille de la simulation.
 * @param rCut : Le rayon à partir duquel la force d'interaction est négligée.
 * @param sigma : La constante présente dans la force d'interaction.
 * @param epsilon : La constante présente dans la force d'interaction.
 * @param cellules : Une table de hachage associant chaque vecteur à une cellule contenant des particules.
 * @param nombreCellule : Le nombre total de cellules dans la simulation.
 * @param conditionLimite : Type de condition limite souhaitée.
 * @param g : Champ gravitationnel.
 * @param energieCinetiqueCible : Energie Cinétique cible donnée par l'utilisateur.
 * @param vtkFile : Booléen permettant de savoir si les fichiers vtk doivent être créés.
 */

class Univers
{
private:
    int nombreParticules = 0;
    Vecteur borneInf = Vecteur();
    Vecteur borneSup = Vecteur();
    Vecteur lD = Vecteur();
    int nombreDimension = 3;
    double rCut = 0;
    int nombreCellule = 0;
    double sigma = 1;
    double epsilon = 5;
    std::unordered_map<Vecteur, std::shared_ptr<Cellule>, Vecteur::HashVecteur> cellules;
    std::vector<std::shared_ptr<Particule>> particules;
    ConditionLimite conditionLimite;
    double G;
    double energieCinetiqueCible;
    bool vtkFile;

public:
    Univers(int, const Vecteur &, const Vecteur &, const Vecteur &, int, double, ConditionLimite = ConditionLimite::Aucune, double = 0, double = 0, bool = false);

    friend std::ostream &operator<<(std::ostream &, const Univers &);

    const std::vector<std::shared_ptr<Particule>> &getParticules() const;
    std::unordered_map<Vecteur, std::shared_ptr<Cellule>, Vecteur::HashVecteur> getCellules();

    /**
     * Cette fonction crée les cellules du maillage en fonction des bornes de l'univers
     * et des dimensions de la maille. Chaque cellule contiendra les particules qui se
     * trouvent à l'intérieur de ses limites.
     */
    void creerCellules();

    /**
     * Cette fonction crée les liens entre les cellules voisines du maillage.
     * Chaque cellule possède une liste de cellules voisines avec lesquelles elle
     * partage des particules.
     */
    void creerVoisinsCellules();

    /**
     * Cette fonction met à jour le maillage en attribuant à chaque particule
     * la cellule correspondant à sa position.
     */
    void updateMaillage();

    /**
     * Cette fonction ajoute une particule à l'univers.
     *
     * @param particule : La particule à ajouter.
     */
    void addParticule(const Particule &particule);

    /**
     * Cette fonction effectue une étape de la méthode de Störmer-Verlet pour
     * la simulation des mouvements des particules. Elle met à jour les positions
     * et les vitesses des particules.
     *
     * @param forces : Un vecteur contenant les forces appliquées sur chaque particule.
     * @param t : Durée de la simulation.
     * @param deltaT : Le pas de temps de la simulation.
     */
    void stromerVerlet(std::vector<Vecteur> forces, double t, double deltaT);

    /**
     * Cette fonction calcule les forces d'interaction entre les particules de l'univers.
     * Elle met à jour les forces de chaque particule en fonction de leurs interactions
     * avec les autres particules.
     */
    void calculForces();

    /**
     * @brief Crée un fichier VTK contenant les données de l'univers à un instant donné.
     *
     * Cette fonction crée un fichier VTK contenant les données de position, vitesse et masse des particules de l'univers à un instant spécifié.
     * Le fichier VTK est créé dans le répertoire "output" avec le nom correspondant à l'instant t.
     *
     * @param t L'instant de temps pour lequel le fichier VTK est créé.
     */
    void creerVTKFile(double t);
};

/**
 * @brief Crée une particule avec des paramètres aléatoires dans les bornes spécifiées.
 *
 * Cette fonction crée une particule avec des paramètres aléatoires dans les bornes spécifiées. Elle génère une masse aléatoire
 * dans l'intervalle [0.005, 0.01] et une position aléatoire en utilisant la fonction randomVecteur. La fonction effectue les
 * vérifications nécessaires pour s'assurer de la validité de la particule créée et génère des exceptions appropriées en cas
 * d'invalidité.
 *
 * @param borneInf La borne inférieure pour les coordonnées de la particule.
 * @param borneSup La borne supérieure pour les coordonnées de la particule.
 * @param nombreDimension Le nombre de dimensions de la particule.
 * @param id L'identifiant de la particule.
 *
 * @throws InvalidPositionParticule Si la position de la particule est invalide.
 *
 * @return La particule créée.
 */
Particule creerParticule(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, int id);

/**
 * @brief Vérifie si un paramètre est positif.
 *
 * Cette fonction vérifie si un paramètre est positif. Elle génère une exception si le paramètre est inférieur à zéro.
 *
 * @param param Le paramètre à vérifier.
 *
 * @throws ParametrePositif Si le paramètre est inférieur à zéro.
 */
void parametrePositif(double param);

/**
 * @brief Vérifie si un paramètre est strictement positif.
 *
 * Cette fonction vérifie si un paramètre est strictement positif. Elle génère une exception si le paramètre est inférieur ou égal à zéro.
 *
 * @param param Le paramètre à vérifier.
 *
 * @throws ParametrePositifStrictement Si le paramètre est inférieur ou égal à zéro.
 */
void parametrePositifStrictement(double param);

/**
 * @brief Vérifie la validité d'un vecteur de longueur caractéristique (lD).
 *
 * Cette fonction vérifie la validité d'un vecteur de longueur caractéristique (lD) en fonction du nombre de dimensions spécifié.
 * Elle génère des exceptions si le nombre de dimensions est invalide, si le vecteur lD a une dimension non nulle supplémentaire
 * par rapport au nombre de dimensions, ou si une composante de lD est inférieure ou égale à zéro.
 *
 * @param lD Le vecteur de longueur caractéristique à vérifier.
 * @param nombreDimension Le nombre de dimensions.
 *
 * @throws DimensionInvalide Si le nombre de dimensions est invalide.
 * @throws ProblemeVecteurDimension Si le vecteur lD a une dimension non nulle supplémentaire par rapport au nombre de dimensions.
 * @throws InvalidLDException Si une composante de lD est inférieure ou égale à zéro.
 */
void verificationLD(const Vecteur &lD, int nombreDimension);
