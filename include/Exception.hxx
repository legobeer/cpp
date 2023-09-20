#include <exception>

/**
 * @class InvalidLDException
 * @brief Exception levée lorsque la longueur caractéristique définie est invalide.
 *
 * Cette exception est lancée lorsque la longueur caractéristique utilisée dans une opération est invalide.
 *
 * Hérite de la classe std::exception.
 */
class InvalidLDException : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "La longueur caractéristique définie est invalide.";
    }
};

/**
 * @class InvalidBorneException
 * @brief Exception levée lorsque la définition des bornes supérieure et inférieure est incorrecte.
 *
 * Cette exception est lancée lorsque la définition des bornes supérieure et inférieure utilisée dans une opération est incorrecte.
 *
 * Hérite de la classe std::exception.
 */
class InvalidBorneException : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "La définition des bornes supérieure et inférieure est incorrecte.";
    }
};

/**
 * @class InvalidPositionParticule
 * @brief Exception levée lorsque la position d'une particule est invalide.
 *
 * Cette exception est lancée lorsque la position d'une particule utilisée dans une opération est invalide.
 *
 * Hérite de la classe std::exception.
 */
class InvalidPositionParticule : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "La position d'une particule est invalide.";
    }
};

/**
 * @class ProblemeVecteurDimension
 * @brief Exception levée lorsque des composantes du vecteur ne sont pas nulles comme attendu selon la dimension de l'espace.
 *
 * Cette exception est lancée lorsque des composantes du vecteur utilisé dans une opération ne sont pas nulles comme attendu en fonction de la dimension de l'espace.
 *
 * Hérite de la classe std::exception.
 */
class ProblemeVecteurDimension : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "Des composantes du vecteur censées être nulles du fait de la dimension de notre espace ne le sont pas.";
    }
};

/**
 * @class ParametrePositif
 * @brief Exception levée lorsque le paramètre doit être positif ou nul.
 *
 * Cette exception est lancée lorsque le paramètre utilisé dans une opération doit être positif ou nul.
 *
 * Hérite de la classe std::exception.
 */
class ParametrePositif : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "Le paramètre doit être positif ou nul.";
    }
};

/**
 * @class ParametrePositifStrictement
 * @brief Exception levée lorsque le paramètre doit être strictement positif.
 *
 * Cette exception est lancée lorsque le paramètre utilisé dans une opération doit être strictement positif.
 *
 * Hérite de la classe std::exception.
 */
class ParametrePositifStrictement : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "Le paramètre doit être strictement positif.";
    }
};

/**
 * @class DimensionInvalide
 * @brief Exception levée lorsque la dimension n'est pas valide.
 *
 * Cette exception est lancée lorsque la dimension utilisée dans une opération n'est pas valide.
 * La dimension doit être comprise entre 1 et 3.
 *
 * Hérite de la classe std::exception.
 */
class DimensionInvalide : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "La dimension doit être comprise entre 1 et 3.";
    }
};

/**
 * @class PositionParticuleInvalide
 * @brief Exception levée lorsque la position de la particule n'est pas dans l'univers.
 *
 * Cette exception est lancée lorsque la position de la particule utilisée dans une opération n'est pas dans l'univers.
 *
 * Hérite de la classe std::exception.
 */
class PositionParticuleInvalide : public std::exception
{
public:
    /**
     * @brief Renvoie le message d'erreur associé à l'exception.
     * @return Le message d'erreur explicatif.
     */
    const char *what() const noexcept override
    {
        return "La position de la particule n'est pas dans l'univers.";
    }
};
