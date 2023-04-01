#include "Particule.hxx"
#include <gtest/gtest.h>

// Test the constructor of the Particule class
TEST(ParticuleTest, ConstructorTest1)
{
    Vecteur position(1, 2, 3);
    Particule p(position, 1.0, 0, 1);

    EXPECT_EQ(p.getPosition(), position);
    EXPECT_EQ(p.getMasse(), 1.0);
    EXPECT_EQ(p.getType(), 0);
    EXPECT_EQ(p.getId(), 1);
    EXPECT_EQ(p.getVitesse(), 0);
}

// Test the constructor of the Particule class
TEST(ParticuleTest, ConstructorTest2)
{
    Vecteur position(1, 2, 3);
    Vecteur vitesse(4, 5, 6);
    Particule p(position, 1.0, 0, 1, vitesse);

    EXPECT_EQ(p.getPosition(), position);
    EXPECT_EQ(p.getMasse(), 1.0);
    EXPECT_EQ(p.getType(), 0);
    EXPECT_EQ(p.getId(), 1);
    EXPECT_EQ(p.getVitesse(), vitesse);
}

// Test the operator== of the Particule class
TEST(ParticuleTest, OperatorEqualsTest)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(1, 1, 1), 1.0, 0, 2, Vecteur(0, 0, 0));
    Particule p3(Vecteur(2, 2, 2), 1.0, 0, 1, Vecteur(0, 0, 0));

    EXPECT_TRUE(p1 == p3);
    EXPECT_FALSE(p1 == p2);
}

// Test the forceGravitationnelleParticule function of the Particule class
TEST(ParticuleTest, ForceGravitationnelleParticuleTest)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 1, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    Vecteur expected_force(0, 0.002, 0); // calculated by hand

    EXPECT_EQ(p1.forceGravitationnelleParticule(p2), expected_force);
}

// Test the forceInteractionFaible function of the Particule class
// avec la distance entre les deux particules plus petite que rCut
TEST(ParticuleTest, ForceInteractionFaibleTest1)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 1, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    std::unordered_set<Particule, Particule::HashParticule> particules = {p1, p2};
    double rCut = 1.5;
    double epsilon = 1.0;
    double sigma = 1.0;

    Vecteur expected_force(0, 0.0005, 0); // calculated by hand

    EXPECT_EQ(p1.forceInteractionFaible(rCut, particules, epsilon, sigma), expected_force);
}

TEST(ParticuleTest, ForceInteractionFaibleTest2)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 1, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    std::unordered_set<Particule, Particule::HashParticule> particules = {p1, p2};
    double rCut = 0.5;
    double epsilon = 1.0;
    double sigma = 1.0;

    Vecteur expected_force(0, 0, 0); // calculated by hand

    EXPECT_EQ(p1.forceInteractionFaible(rCut, particules, epsilon, sigma), expected_force);
}

TEST(ParticuleTest, UpdatePositionTest)
{
    Particule p(Vecteur(1, 2, 3), 1.0, 0, 0, Vecteur(4, 5, 6));
    p.setForce(Vecteur(7, 8, 9));
    double gammaT = 0.1;
    p.updatePosition(gammaT);
    EXPECT_EQ(p.getPosition(), Vecteur(1.432, 2.704, 4.012));
}

TEST(ParticuleTest, UpdateVitesseTest)
{
    Particule p(Vecteur(1, 2, 3), 1.0, 0, 0, Vecteur(4, 5, 6));
    p.setForce(Vecteur(7, 8, 9));
    double gammaT = 0.1;
    Vecteur fOld(10, 11, 12);
    p.updateVitesse(gammaT, fOld);
    EXPECT_EQ(p.getVitesse(), Vecteur(4.696, 5.298, 5.9));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}