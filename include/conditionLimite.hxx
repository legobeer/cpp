enum class ConditionLimite
{
    Reflexion,  ///< Les particules rebondissent contre les frontières.
    Absorption, ///< Les particules sont absorbées aux frontières.
    Periodique, ///< Les frontières sont périodiques, les particules réapparaissent de l'autre côté.
    Aucune      ///< Aucune condition limite n'est appliquée.
};

/**
 * \brief Enumération des conditions limites possibles pour une simulation.
 *
 * Les conditions limites définissent le comportement du système aux frontières.
 */
