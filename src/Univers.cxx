#include "Univers.hxx"
#include <random>
#include <omp.h>
#include "Exception.hxx"
#include <fstream>

Univers::Univers(int nombreParticules, const Vecteur &borneInf, const Vecteur &borneSup, const Vecteur &lD, int nombreDimension, double rCut, ConditionLimite conditionLimite, double G, double energieCinetiqueCible, bool vtkFile) : nombreParticules(nombreParticules), borneInf(borneInf), borneSup(borneSup), lD(lD), nombreDimension(nombreDimension), rCut(rCut), nombreCellule(0), conditionLimite(conditionLimite), G(G), energieCinetiqueCible(energieCinetiqueCible), vtkFile(vtkFile)
{
    for (int i = 0; i < nombreParticules; i++)
    {
        /* À laisser au cas où où doive créer un univers aléatoire. */
        this->particules.push_back(std::make_shared<Particule>(creerParticule(borneInf, borneSup, nombreDimension, i)));
    }
    if (rCut == 0)
        return;
    try
    {
        parametrePositif(nombreParticules);
        parametrePositif(energieCinetiqueCible);
    }
    catch (ParametrePositif &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        parametrePositifStrictement(rCut);
    }
    catch (ParametrePositifStrictement &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        verificationLD(lD, nombreDimension);
    }
    catch (InvalidLDException &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        invalidBorne(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidBorneException &e)
    {
        std::cout << e.what() << std::endl;
    }
    creerCellules();
}

std::ostream &operator<<(std::ostream &, const Univers &u)
{
    for (auto it = u.particules.begin(); it != u.particules.end(); ++it)
        std::cout << **it;
    return std::cout;
}

const std::vector<std::shared_ptr<Particule>> &Univers::getParticules() const { return particules; }

std::unordered_map<Vecteur, std::shared_ptr<Cellule>, Vecteur::HashVecteur> Univers::getCellules() { return cellules; }

void Univers::stromerVerlet(std::vector<Vecteur> fOld, double tEnd, double deltaT)
{
    /* Initialisation des forces */
    if (deltaT == 0)
    {
        return;
    }
    calculForces();
    double t = 0;
    int count = 0;
    double ec = 0;
    double beta = 0;
    while (t < tEnd)
    {

        t += deltaT;
        std::vector<std::shared_ptr<Particule>> particulesASupprimer;

        for (auto &cellule : cellules)
        {
            for (auto &particule : cellule.second->getParticules())
            {
                /* Mis à jour de la position de notre particule à l'instant t + deltaT */
                particule->updatePosition(deltaT);
                // std::cout << particule->getForce() << std::endl;
                fOld[particule->getId()] = particule->getForce();
                /* Mis à 0 de la force de la particule */
                particule->setForce(0);
                ec += 0.5 * particule->getMasse() * particule->getVitesse().computeDistance2(Vecteur());
                if (conditionLimite != ConditionLimite::Aucune && conditionLimite != ConditionLimite::Reflexion && particule->conditionLimiteManager(borneInf, borneSup, nombreDimension, conditionLimite))
                {
                    particulesASupprimer.push_back(particule);
                }
            }
            for (const auto &particule : particulesASupprimer)
            {
                nombreParticules--;
                cellule.second->deleteParticule(particule);
            }
        }
        if (vtkFile && ((double)count / 10 - count / 10) == 0)
        {
            creerVTKFile(t);
        }
        updateMaillage();
        /* Calcul des forces à l'instant t + deltaT */
        calculForces();
        if (count == 1000 && energieCinetiqueCible != 0)
        {
            beta = std::sqrt(energieCinetiqueCible / ec);
        }

        /* Mis à jour de la vitesse de la particule */
        for (auto &cellule : cellules)
        {
            for (auto &particule : cellule.second->getParticules())
            {
                if (conditionLimite == ConditionLimite::Reflexion && particule->conditionLimiteManager(borneInf, borneSup, nombreDimension, conditionLimite))
                    continue;
                try
                {
                    particule->invalidParticule(borneInf, borneSup, nombreDimension);
                }
                catch (InvalidPositionParticule &e)
                {
                    std::cout << e.what() << std::endl;
                }
                particule->updateVitesse(deltaT, fOld[particule->getId()]);
                /* À supprimer c'est pour calculer la durée d'une itération */
                if (count == 1000 && energieCinetiqueCible != 0)
                {
                    Vecteur vitesse = particule->getVitesse();

                    vitesse *= beta;

                    particule->setVitesse(vitesse);
                }
            }
        }

        if (count == 1000)
            count = 0;
        count++;
    }
}

void Univers::addParticule(const Particule &p)
{
    try
    {
        p.invalidParticule(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidPositionParticule &e)
    {
        std::cout << e.what() << std::endl;
    }
    this->particules.push_back(std::make_shared<Particule>(p));
}

void Univers::creerCellules()
{
    cellules.clear(); /* Vide le contenu précédent de cellules */
    for (const auto &particule : particules)
    {
        const Vecteur &positionParticule = particule->getPosition();
        const Vecteur &positionMaillage = positionParticule.attributionMaillage(rCut);

        auto it = cellules.find(positionMaillage);
        if (it == cellules.end())
        {
            /* Crée une nouvelle cellule et l'ajoute à l'attribut cellules */
            std::shared_ptr<Cellule> nouvelleCellule = std::make_shared<Cellule>(nombreCellule++, positionMaillage, nombreDimension);
            nouvelleCellule->addParticule(particule);
            cellules.emplace(positionMaillage, nouvelleCellule);
        }
        else
        {
            /* Ajoute la particule à la cellule existante */
            it->second->addParticule(particule);
        }
    }

    /* Calcule les voisins des cellules */
    creerVoisinsCellules();
}

void Univers::creerVoisinsCellules()
{
    for (auto &cellule : cellules)
    {
        const Vecteur &coordonnees = cellule.first;
        std::shared_ptr<Cellule> &cellulePtr = cellule.second;

        for (const Vecteur &voisin : coordonnees.getVoisins(nombreDimension))
        {
            auto it = cellules.find(voisin);
            if (it != cellules.end())
            {
                /* Il y a une particule dans la cellule voisine
                donc on l'ajoute aux cellules voisines de la cellule courante */
                std::shared_ptr<Cellule> &voisinPtr = it->second;
                cellulePtr->addCelluleVoisine(voisinPtr);
            }
        }
    }
}

void Univers::calculForces()
{
    // Création d'un vecteur d'itérateurs pour stocker les itérateurs des éléments de la map
    std::vector<std::unordered_map<Vecteur, std::shared_ptr<Cellule>, Vecteur::HashVecteur>::iterator> iters;

    // Parcours de la map et stockage des itérateurs dans le vecteur
    for (auto it = cellules.begin(); it != cellules.end(); ++it)
    {
        iters.push_back(it);
    }

// Boucle for parallèle pour traiter les éléments de manière simultanée
#pragma omp parallel for
    for (size_t i = 0; i < iters.size(); ++i)
    {
        const auto p = iters[i];
        const auto &particules = p->second->getParticules();

        for (const auto &particule : particules)
        {
            Vecteur force = 0;

            // Force avec les particules dans la même maille
            force += particule->calculForce(rCut, particules, epsilon, sigma, G);

            for (const auto &celluleVoisine : p->second->getCellulesVoisines())
            {
                // Force avec les particules des cellules voisines
                force += particule->calculForce(rCut, celluleVoisine->getParticules(), epsilon, sigma);
            }

            // Mise à jour de la force d'interaction faible
            const Vecteur &forceActuelle = particule->getForce();
            particule->setForce(force + forceActuelle);
        }
    }
}

void Univers::updateMaillage()
{
    Vecteur positionMaillage;
    Vecteur positionParticule;

    for (auto p = cellules.begin(); p != cellules.end(); p++)
    {
        std::vector<std::shared_ptr<Particule>> particulesASupprimer;

        for (const auto &particule : p->second->getParticules())
        {
            positionParticule = particule->getPosition();
            positionMaillage = positionParticule.attributionMaillage(rCut);

            if (!(p->first == positionMaillage))
            {
                /* Il faut changer la position de la particule dans le maillage */
                particulesASupprimer.push_back(particule);
                /* on ajoute la particule au bon endroit */
                if (cellules.find(positionMaillage) == cellules.end())
                {
                    /* Une case vide précédemment contient une particule
                    donc on l'ajoute au map */
                    const std::shared_ptr<Cellule> &cellule = std::make_shared<Cellule>(nombreCellule, positionMaillage, nombreDimension);
                    cellules[positionMaillage] = cellule;

                    const std::vector<Vecteur> &voisinsPossibles = cellule->getVoisins();
                    for (size_t j = 0; j < voisinsPossibles.size(); ++j)
                    {
                        const Vecteur &voisinPotentiel = voisinsPossibles[j];
                        auto it = cellules.find(voisinPotentiel);
                        if (it != cellules.end())
                        {
                            /* La cellule possède un nouveau voisin on l'ajoute alors. */
                            const std::shared_ptr<Cellule> &tmp = cellules[positionMaillage];
                            tmp->addCelluleVoisine(cellule);
                            cellule->addCelluleVoisine(tmp);
                        }
                    }
                    nombreCellule++;
                }
                cellules[positionMaillage]->addParticule(particule);
                /* On vérifie si la liste des particules n'est pas vide
                si elle est vide on supprime la cellule du map*/
                if (p->second->getParticules().size() == 0)
                    cellules.erase(p->first);
            }
        }
        for (const auto &particule : particulesASupprimer)
        {
            p->second->deleteParticule(particule);
        }
    }
}

void Univers::creerVTKFile(double t)
{
    std::string nomFichier = "output_" + std::to_string(t) + ".vtk";
    std::ofstream fichier(nomFichier);
    if (fichier.is_open())
    {
        fichier << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
        fichier << "<UnstructuredGrid>\n";
        fichier << "<Piece NumberOfPoints=\"" << nombreParticules << "\" NumberOfCells=\"0\">\n";
        fichier << "<Points>\n";
        fichier << "<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
        for (auto &cellule : cellules)
        {
            for (auto &particule : cellule.second->getParticules())
            {
                fichier << particule->getPosition() << " ";
            }
        }
        fichier << "\n";
        fichier << "</DataArray>\n";
        fichier << "</Points>\n";
        fichier << "<PointData Vectors=\"vector\">\n";
        fichier << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
        for (auto &cellule : cellules)
        {
            for (auto &particule : cellule.second->getParticules())
            {
                fichier << particule->getVitesse() << " ";
            }
        }
        fichier << "\n";
        fichier << "</DataArray>\n";
        fichier << "<DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
        for (auto &cellule : cellules)
        {
            for (auto &particule : cellule.second->getParticules())
            {
                fichier << particule->getMasse() << " ";
            }
        }
        fichier << "\n";
        fichier << "</DataArray>\n";
        fichier << "</PointData>\n";
        fichier << "<Cells>\n";
        fichier << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
        fichier << "</DataArray>\n";
        fichier << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
        fichier << "</DataArray>\n";
        fichier << "<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
        fichier << "</DataArray>\n";
        fichier << "</Cells>\n";
        fichier << "</Piece>\n";
        fichier << "</UnstructuredGrid>\n";
        fichier << "</VTKFile>\n";
        fichier.close();
    }
    else
    {
        std::cout << "Le fichier n'a pu être ouvert." << std::endl;
        exit(1);
    }
}

Particule creerParticule(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, int id)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.005, 0.01);
    double masse = dist(mt);
    Particule p = Particule(randomVecteur(nombreDimension, borneInf, borneSup), masse, 0, id, Vecteur());
    try
    {
        p.invalidParticule(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidPositionParticule &e)
    {
        std::cout << e.what() << std::endl;
    }
    return p;
}

void parametrePositif(double param)
{
    if (param < 0)
        throw ParametrePositif();
}

void parametrePositifStrictement(double param)
{
    if (!(param > 0))
        throw ParametrePositifStrictement();
}

void verificationLD(const Vecteur &lD, int nombreDimension)
{
    try
    {
        dimensionInvalide(nombreDimension);
    }
    catch (DimensionInvalide &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        vecteurInvalide(nombreDimension, lD);
    }
    catch (ProblemeVecteurDimension &e)
    {
        std::cout << e.what() << std::endl;
    }
    if (nombreDimension > 0)
    {
        if (lD.getX() <= 0)
            throw InvalidLDException();
    }
    if (nombreDimension > 1)
    {
        if (lD.getY() <= 0)
            throw InvalidLDException();
    }
    if (nombreDimension > 2)
    {
        if (lD.getZ() <= 0)
            throw InvalidLDException();
    }
}
