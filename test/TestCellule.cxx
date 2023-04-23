#include "Cellule.hxx"
#include "Vecteur.hxx"
#include <gtest/gtest.h>
#include <memory>

class CelluleTest : public ::testing::Test
{
protected:
    // Create a new cell for each test
    void SetUp() override
    {
        cellule = new Cellule();
    }

    // Delete the cell after each test
    void TearDown() override
    {
        delete cellule;
    }

    // Pointer to the cell being tested
    Cellule *cellule;
};

// Test adding a particle to a cell
TEST_F(CelluleTest, AddParticule)
{
    Particule p1(Vecteur(0, 2, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    cellule->addParticule(std::make_shared<Particule>(p1));
    std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> particules = cellule->getParticules();
    ASSERT_EQ(particules.size(), 1);
    ASSERT_EQ(**particules.begin(), p1);
}

// Test adding a neighboring cell to a cell
TEST_F(CelluleTest, AddCelluleVoisine)
{
    Vecteur v1(1, 0, 0);
    cellule->addCelluleVoisine(v1);
    std::unordered_set<Vecteur, Vecteur::HashVecteur> voisins = cellule->getCellulesVoisines();
    ASSERT_EQ(voisins.size(), 1);
    ASSERT_EQ(*voisins.begin(), v1);
}

// Test deleting a particle from a cell
TEST_F(CelluleTest, DeleteParticule)
{
    Particule p1(Vecteur(0, 2, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    std::shared_ptr<Particule> particule = std::make_shared<Particule>(p1);
    cellule->addParticule(particule);
    cellule->deleteParticule(particule);
    std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> particules = cellule->getParticules();
    ASSERT_EQ(particules.size(), 0);
}

// Test deleting a neighboring cell from a cell
TEST_F(CelluleTest, DeleteVoisin)
{
    Vecteur v1(1, 0, 0);
    cellule->addCelluleVoisine(v1);
    cellule->deleteVoisin(v1);
    std::unordered_set<Vecteur, Vecteur::HashVecteur> voisins = cellule->getCellulesVoisines();
    ASSERT_EQ(voisins.size(), 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}