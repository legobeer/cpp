#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <vector>
#include <chrono>
#include <iostream>
#include <list>
#include <cmath>

int main()
{

    std::list<int> nombreParticules;
    nombreParticules.push_back(pow(2, 9));
    nombreParticules.push_back(pow(2, 12));
    nombreParticules.push_back(pow(2, 15));
    nombreParticules.push_back(pow(2, 18));
    nombreParticules.push_back(pow(2, 21));
    for (int nombreParticule : nombreParticules)
    {
        auto start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
        Univers u = Univers(nombreParticule, Vecteur(), Vecteur(1, 1, 1), 0, 3, 0);
        auto end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
                                                                   // calcul du temps écoulé en nanosecondes
        auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();
        std::cout << "Temps écoulé insertion de " << nombreParticule << " : " << duration_sec << " s" << std::endl;
        if (nombreParticule < pow(2, 18))
        {
            start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
            u.calculForcesGravitationnelles();
            end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
                                                                  // calcul du temps écoulé en nanosecondes
            duration_sec = std::chrono::duration<double>(end_time - start_time).count();
            std::cout << "Temps écoulé calcul des forces d'interaction gravitationnelles de " << nombreParticule << " : " << duration_sec << " s" << std::endl;
        }
    }
}