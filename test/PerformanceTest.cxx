#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <vector>
#include <chrono>
#include <iostream>

int main()
{

    auto start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
    Univers u = Univers(8000, Vecteur(), Vecteur(1, 1, 1), 0, 3, 0);
    auto end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
                                                               // calcul du temps écoulé en nanosecondes
    auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Temps écoulé : " << duration_sec << " s" << std::endl;

    start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
    u.calculForcesGravitationnelles();
    end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
                                                          // calcul du temps écoulé en nanosecondes
    duration_sec = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Temps écoulé : " << duration_sec << " s" << std::endl;
}