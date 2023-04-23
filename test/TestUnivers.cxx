#include <gtest/gtest.h>
#include "Univers.hxx"

// Tests the Univers constructor.
TEST(UniversTest, Constructor)
{
    // Test the constructor without rCut
    int nombreParticules = 10;
    Vecteur borneInf(0, 0, 0);
    Vecteur borneSup(1, 1, 1);
    int nombreDimension = 3;

    Univers univers(nombreParticules, borneInf, borneSup, nombreDimension);

    EXPECT_EQ(univers.getNombreParticules(), nombreParticules);
    EXPECT_EQ(univers.getParticules().size(), static_cast<size_t>(nombreParticules));

    // Test the constructor with rCut
    double rCut = 0.5;

    Univers univers2(nombreParticules, borneInf, borneSup, nombreDimension, rCut);

    EXPECT_EQ(univers2.getNombreParticules(), nombreParticules);
    EXPECT_EQ(univers2.getParticules().size(), static_cast<size_t>(nombreParticules));
    EXPECT_GE(univers2.getCellules().size(), 1);
}

// Tests the stromerVerlet method.
TEST(UniversTest, StromerVerlet)
{
    // Initialize an Univers object
    int nombreParticules = 10;
    Vecteur borneInf(0, 0, 0);
    Vecteur borneSup(1, 1, 1);
    int nombreDimension = 3;
    double rCut = 0.5;

    Univers univers(nombreParticules, borneInf, borneSup, nombreDimension, rCut);

    // Set the initial forces and positions
    std::vector<Vecteur> fOld(nombreParticules);
    for (int i = 0; i < nombreParticules; i++)
    {
        fOld[i] = randomVecteur(nombreDimension, borneInf, borneSup);
        univers.getParticules().front().setPosition(randomVecteur(nombreDimension, borneInf, borneSup));
    }

    // Test the stromerVerlet method with deltaT = 0
    double tEnd = 1;
    double deltaT = 0;

    univers.stromerVerlet(fOld, tEnd, deltaT);

    // All particles should have the same position
    std::vector<Particule> particules = univers.getParticules();
    EXPECT_TRUE(std::all_of(particules.begin(), particules.end(), [&](Particule particule)
                            { for (Particule &p : particules) {
                                if (p.getId() == particule.getId()) 
                                    return p.getPosition() == particule.getPosition();
                                } return false; }));

    // Test the stromerVerlet method with deltaT > 0
    tEnd = 10;
    deltaT = 0.1;
    univers.stromerVerlet(fOld, tEnd, deltaT);
    // All particles should have moved
    std::vector<Particule> particules2 = univers.getParticules();
    EXPECT_FALSE(std::all_of(particules2.begin(), particules2.end(), [&](Particule particule)
                             { for (Particule p : particules) {
                                if (p.getId() == particule.getId()) {
                                    return p.getPosition() == particule.getPosition();
                                }
                            } return true; }));
}

// Test de la fonction addParticule
TEST(UniversTest, addParticuleTest)
{
    int nombreParticules = 0;
    Vecteur borneInf(0, 0, 0);
    Vecteur borneSup(1, 1, 1);
    int nombreDimension = 3;

    Univers univers(nombreParticules, borneInf, borneSup, nombreDimension);

    Particule p(Vecteur(), 3, 0, 0);
    univers.addParticule(p);
    EXPECT_EQ(univers.getParticules().size(), 1);
    EXPECT_TRUE(univers.getParticules().front() == p);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}