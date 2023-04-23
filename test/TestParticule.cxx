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
    Particule p1(Vecteur(0, 0, 0), 10.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 2, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    Vecteur expected_force(0, 40.0 / 8, 0); // calculated by hand

    EXPECT_EQ(p1.forceGravitationnelleParticule(p2), expected_force);
}

// Test the forceInteractionFaible function of the Particule class
// avec la distance entre les deux particules plus petite que rCut
TEST(ParticuleTest, ForceInteractionFaibleTest1)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 1, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> particules = {std::make_shared<Particule>(p1), std::make_shared<Particule>(p2)};
    double rCut = 1.5;
    double epsilon = 1.0;
    double sigma = 1.0;

    Vecteur expected_force(0, -24, 0); // calculated by hand

    EXPECT_EQ(p1.forceInteractionFaible(rCut, particules, epsilon, sigma), expected_force);
}

TEST(ParticuleTest, ForceInteractionFaibleTest2)
{
    Particule p1(Vecteur(0, 0, 0), 1.0, 0, 1, Vecteur(0, 0, 0));
    Particule p2(Vecteur(0, 1, 0), 2.0, 0, 2, Vecteur(0, 0, 0));

    std::unordered_set<std::shared_ptr<Particule>, Particule::HashParticulePtr> particules = {std::make_shared<Particule>(p1), std::make_shared<Particule>(p2)};
    double rCut = 0.5;
    double epsilon = 1.0;
    double sigma = 1.0;

    Vecteur expected_force(0, 0, 0); // calculated by hand

    EXPECT_EQ(p1.forceInteractionFaible(rCut, particules, epsilon, sigma), expected_force);
}

TEST(ParticuleTest, UpdatePositionTest)
{
    Particule p(Vecteur(1, 2, 3), 10.0, 0, 0, Vecteur(4, 5, 6));
    p.setForce(Vecteur(7, 8, 9));
    double deltaT = 0.1;
    p.updatePosition(deltaT);
    EXPECT_EQ(p.getPosition(), Vecteur(1.4035, 2.504, 3.6045));
}

TEST(ParticuleTest, UpdateVitesseTest)
{
    Particule p(Vecteur(1, 2, 3), 100, 0, 0, Vecteur(4, 5, 6));
    p.setForce(Vecteur(7, 8, 9));
    double deltaT = 0.1;
    Vecteur fOld(10, 11, 12);
    p.updateVitesse(deltaT, fOld);
    EXPECT_EQ(p.getVitesse(), Vecteur(4.0085, 5.0095, 6.0105));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}