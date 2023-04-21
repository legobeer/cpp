#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <vector>

int main()
{
    /* Création de l'univers */
    Univers u = Univers(0, Vecteur(), Vecteur(), Vecteur(250, 240), 2, 2.5);
    /* Ajout des particules du cube */
    double x, y = 0;
    for (int i = 0; i < 40; i++)
    {
        x = 0;
        for (int j = 0; j < 40; j++)
        {
            u.addParticule(Particule(Vecteur(x, y), 1, 0, i * j + j, Vecteur(0, 10)));
            x += pow(2, 1.0 / 6);
        }
        y += pow(2, 1.0 / 6);
    }
    /* Ajout particule du rectangle */
    /* On ajoute un léger offset au y */
    y = 50 * pow(2, 1.0 / 6);
    /* On ajoute un offset au x pour centrer le rectangle par rapport au cube */
    for (int j = 0; j < 40; j++)
    {
        x = -60 * pow(2, 1.0 / 6);
        for (int i = 0; i < 160; i++)
        {
            u.addParticule(Particule(Vecteur(x, y), 1, 1, 160 + i * j + j));
            x += pow(2, 1.0 / 6);
        }
        y += pow(2, 1.0 / 6);
    }
    /* On a constitué notre univers */
    /* On crée les cellules */
    u.creerCellules();
    /* On effectue la simulation */
    std::vector<Vecteur> fOld(8000, Vecteur());
    u.stromerVerlet(fOld, 19.5, 0.00005);
}