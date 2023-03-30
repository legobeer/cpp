#include "Particule.hxx"

int main()
{
    Particule particule1 = Particule(Vecteur(1, 0.5, 0.25), 3.5, 2, 1);
    std::cout << particule1 << std::endl;
}