#include "Vecteur.hxx"

int main()
{
    Vecteur vecteur1 = Vecteur(1.0, 2.0, 3.5);
    Vecteur vecteur2 = Vecteur(1.2, 3.0, 5.5);
    double scalar = 2.5;
    vecteur1.displayVector();
    vecteur1.multiplyScalar(scalar);
    vecteur1.displayVector();
    vecteur1.addVectors(vecteur2);
    vecteur1.displayVector();
    Vecteur direction = vecteur1.getDirection(vecteur2);
    direction.displayVector();
    vecteur1.setVecteur(direction);
    vecteur1.displayVector();
    return 0;
}