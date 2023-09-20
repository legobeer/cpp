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

    Univers univers(nombreParticules, borneInf, borneSup, Vecteur(), nombreDimension, 0);

    EXPECT_EQ(univers.getParticules().size(), static_cast<size_t>(nombreParticules));

    // Test the constructor with rCut
    double rCut = 0.5;

    Univers univers2(nombreParticules, borneInf, borneSup, Vecteur(), nombreDimension, rCut);

    EXPECT_EQ(univers2.getParticules().size(), static_cast<size_t>(nombreParticules));
    EXPECT_GE(univers2.getCellules().size(), 1);
}

// Test de la fonction addParticule
TEST(UniversTest, addParticuleTest)
{
    int nombreParticules = 0;
    Vecteur borneInf(0, 0, 0);
    Vecteur borneSup(1, 1, 1);
    int nombreDimension = 3;

    Univers univers(nombreParticules, borneInf, borneSup, Vecteur(), nombreDimension, 0);

    Particule p(Vecteur(), 3, 0, 0, Vecteur());
    univers.addParticule(p);
    EXPECT_EQ(univers.getParticules().size(), 1);
    EXPECT_TRUE(*univers.getParticules().front() == p);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}