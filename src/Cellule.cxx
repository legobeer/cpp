#include "Cellule.hxx"

Cellule::Cellule(int id, const Vecteur &position, int dimension) : id(id)
{
    this->voisins = position.getVoisins(dimension);
}

bool Cellule::operator==(const Cellule &otherCellule) const
{
    if (this->id == otherCellule.id)
        return true;
    else
        return false;
};

const std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> &Cellule::getParticules() const
{
    return particules;
}

const std::unordered_set<std::shared_ptr<Cellule>, Cellule::HashCellulePtr> &Cellule::getCellulesVoisines() const
{
    return cellulesVoisines;
}

const std::vector<Vecteur> &Cellule::getVoisins() const
{
    return voisins;
}

void Cellule::addParticule(std::shared_ptr<Particule> particule)
{
    particules.emplace(particule);
}

void Cellule::addCelluleVoisine(std::shared_ptr<Cellule> celluleVoisine)
{
    cellulesVoisines.emplace(celluleVoisine);
}

void Cellule::deleteParticule(std::shared_ptr<Particule> particule)
{

    auto it = particules.find(particule);
    if (it != particules.end())
    {
        particules.erase(it);
    }
}

void Cellule::deleteVoisin(std::shared_ptr<Cellule> voisin)
{
    auto it = cellulesVoisines.find(voisin);
    if (it != cellulesVoisines.end())
    {
        cellulesVoisines.erase(it);
    }
}
