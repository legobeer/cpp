#include "Vecteur.hxx"
#include <iostream>
#include <gtest/gtest.h>

TEST(VecteurTest, TestInitialisation1)
{
    Vecteur v(1.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0);
}

TEST(VecteurTest, TestInitialisation2)
{
    Vecteur v(1.0, 2.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0);
}

TEST(VecteurTest, TestInitialisation3)
{
    Vecteur v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(VecteurTest, TestSetters)
{
    Vecteur v(1.0, 2.0, 3.0);
    v.setXInt(4);
    v.setYInt(5);
    v.setZInt(6);
    EXPECT_DOUBLE_EQ(v.getX(), 4);
    EXPECT_DOUBLE_EQ(v.getY(), 5);
    EXPECT_DOUBLE_EQ(v.getZ(), 6);
}

TEST(VecteurTest, TestAddition)
{
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    Vecteur v3 = v1 + v2;
    EXPECT_DOUBLE_EQ(v3.getX(), 5.0);
    EXPECT_DOUBLE_EQ(v3.getY(), 7.0);
    EXPECT_DOUBLE_EQ(v3.getZ(), 9.0);
}

TEST(VecteurTest, TestSubtraction)
{
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    Vecteur v3 = v1 - v2;
    EXPECT_DOUBLE_EQ(v3.getX(), -3.0);
    EXPECT_DOUBLE_EQ(v3.getY(), -3.0);
    EXPECT_DOUBLE_EQ(v3.getZ(), -3.0);
}

TEST(VecteurTest, TestMultiplication)
{
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    v1 *= v2;
    EXPECT_DOUBLE_EQ(v1.getX(), 4.0);
    EXPECT_DOUBLE_EQ(v1.getY(), 10.0);
    EXPECT_DOUBLE_EQ(v1.getZ(), 18.0);
}

TEST(VecteurTest, TestNegation)
{
    Vecteur v(1.0, 2.0, 3.0);
    v = -v;
    EXPECT_DOUBLE_EQ(v.getX(), -1.0);
    EXPECT_DOUBLE_EQ(v.getY(), -2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), -3.0);
}

TEST(VecteurTest, TestEquality)
{
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(1.0, 2.0, 3.0);
    EXPECT_TRUE(v1 == v2);
}

TEST(VecteurTest, MultiplicationScalaire)
{
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2 = v1 * 3;
    EXPECT_DOUBLE_EQ(v2.getX(), 3);
    EXPECT_DOUBLE_EQ(v2.getY(), 6);
    EXPECT_DOUBLE_EQ(v2.getZ(), 9);
}

TEST(VecteurTest, DoubleAssignement)
{
    Vecteur v;
    v = 3;
    EXPECT_DOUBLE_EQ(v.getX(), 3);
    EXPECT_DOUBLE_EQ(v.getY(), 3);
    EXPECT_DOUBLE_EQ(v.getZ(), 3);
}

TEST(VecteurTest, TestMaillage)
{
    Vecteur v(1.5, 2.5, 3.5);
    Vecteur maillage = v.attributionMaillage(1.0);
    EXPECT_EQ(maillage.getX(), 1);
    EXPECT_EQ(maillage.getY(), 2);
    EXPECT_EQ(maillage.getZ(), 3);
}

TEST(VecteurTest, GetDirection)
{
    Vecteur v1(1, 2, 3);
    Vecteur v2(4, 5, 6);
    Vecteur direction = v1.getDirection(v2);

    ASSERT_EQ(direction.getX(), 3);
    ASSERT_EQ(direction.getY(), 3);
    ASSERT_EQ(direction.getZ(), 3);
}

TEST(VecteurTest, ComputeDistance)
{
    Vecteur v1(1, 2, 3);
    Vecteur v2(4, 5, 6);
    double distance = v1.computeDistance(v2);

    ASSERT_DOUBLE_EQ(distance, 5.196152422706632);
}

TEST(VecteurTest, GetVoisins)
{
    Vecteur v1(1, 2, 3);
    std::vector<Vecteur> voisins1 = v1.getVoisins(1);
    ASSERT_EQ(voisins1.size(), 2);
    ASSERT_EQ(voisins1[0], Vecteur(0, 2, 3));
    ASSERT_EQ(voisins1[1], Vecteur(2, 2, 3));

    std::vector<Vecteur> voisins2 = v1.getVoisins(2);
    ASSERT_EQ(voisins2.size(), 8);
    int i = 0;
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            if (!(y == 0 && x == 0))
            {
                ASSERT_EQ(voisins2[i], Vecteur(v1.getX() + x, v1.getY() + y, v1.getZ()));
                i++;
            }
        }
    }

    std::vector<Vecteur> voisins3 = v1.getVoisins(3);
    ASSERT_EQ(voisins3.size(), 26);
    i = 0;
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            for (int z = -1; z < 2; z++)
            {
                if (!(y == 0 && x == 0 && z == 0))
                {
                    ASSERT_EQ(voisins3[i], Vecteur(v1.getX() + x, v1.getY() + y, v1.getZ() + z));
                    i++;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}