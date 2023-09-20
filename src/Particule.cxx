#include "Particule.hxx"
#include <iostream>
#include "Exception.hxx"

Particule::Particule(Vecteur position, double masse, int type, int id, Vecteur vitesse) : position(position), vitesse(vitesse), force(Vecteur()), masse(masse), type(type), id(id)
{

    try
    {
        if (!(masse > 0))
            throw ParametrePositifStrictement();
    }
    catch (ParametrePositifStrictement &e)
    {
        std::cout << e.what() << std::endl;
    }
}

bool Particule::operator==(const Particule &otherParticule) const
{
    if (this->id == otherParticule.id)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &os, const Particule &p)
{
    std::cout << "Particule n°" << p.id << "\nPosition : " << p.position << std::endl;
    std::cout << "Masse : " << p.masse << "\nType : " << p.type << "\nVitesse : " << p.vitesse << std::endl;
    std::cout << "Force : " << p.force << std::endl;
    std::cout << "------------------------------------";
    return os;
}

const Vecteur &Particule::getVitesse() const { return vitesse; }
const Vecteur &Particule::getPosition() const { return position; }
const Vecteur &Particule::getForce() const { return force; }
int Particule::getId() const { return id; }
double Particule::getMasse() const { return masse; }
int Particule::getType() const { return type; }

void Particule::setForce(const Vecteur &force) { this->force = force; }
void Particule::setPosition(const Vecteur &position) { this->position = position; }
void Particule::setVitesse(const Vecteur &vitesse) { this->vitesse = vitesse; }

Vecteur Particule::forceGravitationnelleParticule(const Particule &particule) const
{
    const Vecteur &pos = particule.getPosition();
    Vecteur direction = position.getDirection(pos);
    const double distance2 = position.computeDistance2(pos);
    direction *= masse * particule.getMasse() / (distance2 * std::sqrt(distance2));
    return direction;
}

Vecteur Particule::calculForce(double rCut, const std::unordered_set<std::shared_ptr<Particule>, HashParticulePtr> &particules, double epsilon, double sigma, double G) const
{
    Vecteur force = Vecteur(0, masse * G, 0);
    double r2 = 0;
    Vecteur tmp;
    for (const auto &particule : particules)
    {
        if (id != particule->getId())
        {
            r2 = position.computeDistance2(particule->getPosition());
            if (r2 < rCut * rCut)
            {
                /* Forces interactions faibles */
                const double r6 = pow(sigma, 6) / (r2 * r2 * r2);
                const double coeff = 24 * epsilon * (1 - 2 * r6) * r6 / (r2);
                tmp = position.getDirection(particule->getPosition()) * coeff;
                /* Forces gravitationnelles */
                tmp += this->forceGravitationnelleParticule(*particule);
            }
            force += tmp;
        }
    }

    return force;
}

void Particule::updatePosition(double deltaT)
{
    position += (force * (0.5 / masse * deltaT) + vitesse) * deltaT;
}

void Particule::updateVitesse(double deltaT, Vecteur fOld)
{
    vitesse += (force + fOld) * (0.5 * deltaT / masse);
}

void Particule::conditionLimiteReflexion(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, double epsilon, double sigma)
{
    try
    {
        invalidBorne(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidBorneException &e)
    {
        std::cout << e.what() << std::endl;
    }
    double rCut = pow(2, (double)1 / 6) * sigma;
    double rCut2 = rCut * rCut;
    double r2 = Vecteur(position.getX()).computeDistance2(Vecteur(borneInf.getX()));

    if (nombreDimension > 0 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(-12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
    r2 = Vecteur(position.getX()).computeDistance2(Vecteur(borneSup.getX()));
    if (nombreDimension > 0 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
    r2 = Vecteur(0, position.getY()).computeDistance2(Vecteur(0, borneInf.getY()));
    if (nombreDimension > 1 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(0, -12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
    r2 = Vecteur(0, position.getY()).computeDistance2(Vecteur(0, borneSup.getY()));
    if (nombreDimension > 1 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(0, 12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
    r2 = Vecteur(0, 0, position.getZ()).computeDistance2(Vecteur(0, 0, borneInf.getZ()));
    if (nombreDimension > 2 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(0, 0, -12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
    r2 = Vecteur(0, 0, position.getZ()).computeDistance2(Vecteur(0, 0, borneSup.getZ()));
    if (nombreDimension > 2 && r2 < rCut2)
    {
        double r6 = (sigma / (4 * r2)) * (sigma / (4 * r2)) * (sigma / (4 * r2));
        force += Vecteur(0, 0, 12 * epsilon * r6 * (1 - 2 * r6) / std::sqrt(r2));
    }
}

bool Particule::conditionLimiteManager(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension, ConditionLimite conditionLimite, double epsilon, double sigma)
{
    try
    {
        invalidBorne(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidBorneException &e)
    {
        std::cout << e.what() << std::endl;
    }
    // if (conditionLimite == ConditionLimite::Reflexion)
    // {
    //     conditionLimiteReflexion(borneInf, borneSup, nombreDimension, epsilon, sigma);
    // }
    const Vecteur respectBorneInf = -borneInf + position;
    const Vecteur respectBorneSup = -position + borneSup;
    if (nombreDimension > 0)
    {
        if (respectBorneInf.getX() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
            {
                return true;
            }
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(borneSup.getX(), position.getY(), position.getZ());
            else
            {
                vitesse = Vecteur(-vitesse.getX(), vitesse.getY(), vitesse.getZ());

                return true;
            }
        }
        if (respectBorneSup.getX() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
                return true;
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(borneInf.getX(), position.getY(), position.getZ());
            else
            {
                vitesse = Vecteur(-vitesse.getX(), vitesse.getY(), vitesse.getZ());
                return true;
            }
        }
    }
    if (nombreDimension > 1)
    {
        if (respectBorneInf.getY() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
                return true;
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(position.getX(), borneSup.getY(), position.getZ());
            else
            {
                vitesse = Vecteur(vitesse.getX(), -vitesse.getY(), vitesse.getZ());
                return true;
            }
        }
        if (respectBorneSup.getY() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
                return true;
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(position.getX(), borneInf.getY(), position.getZ());
            else
            {
                vitesse = Vecteur(vitesse.getX(), -vitesse.getY(), vitesse.getZ());
                return true;
            }
        }
    }
    if (nombreDimension > 2)
    {
        if (respectBorneInf.getZ() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
                return true;
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(position.getX(), position.getY(), borneSup.getZ());
            else
            {
                vitesse = Vecteur(vitesse.getX(), vitesse.getY(), -vitesse.getZ());
                return true;
            }
        }
        if (respectBorneSup.getZ() <= 0)
        {
            if (conditionLimite == ConditionLimite::Absorption)
                return true;
            if (conditionLimite == ConditionLimite::Periodique)
                position = Vecteur(position.getX(), position.getY(), borneInf.getZ());
            else
            {
                vitesse = Vecteur(vitesse.getX(), vitesse.getY(), -vitesse.getZ());
                return true;
            }
        }
    }
    return false;
}

void Particule::invalidParticule(const Vecteur &borneInf, const Vecteur &borneSup, int nombreDimension) const
{
    try
    {
        invalidBorne(borneInf, borneSup, nombreDimension);
    }
    catch (InvalidBorneException &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        vecteurInvalide(nombreDimension, position);
        vecteurInvalide(nombreDimension, vitesse);
        vecteurInvalide(nombreDimension, force);
    }
    catch (ProblemeVecteurDimension &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        if (!(masse > 0))
            throw ParametrePositifStrictement();
    }
    catch (ParametrePositifStrictement &e)
    {
        std::cout << e.what() << std::endl;
    }

    const Vecteur &tmp1 = -borneInf + position;
    const Vecteur &tmp2 = -position + borneSup;
    if (nombreDimension > 0)
    {
        if (tmp1.getX() < 0 || tmp2.getX() < 0)
            throw InvalidPositionParticule();
    }
    if (nombreDimension > 1)
    {
        if (tmp1.getY() < 0 || tmp2.getY() < 0)
            throw InvalidPositionParticule();
    }
    if (nombreDimension > 2)
    {
        if (tmp1.getZ() < 0 || tmp2.getZ() < 0)
            throw InvalidPositionParticule();
    }
}
