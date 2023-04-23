#include "Particule.hxx"
#include "Univers.hxx"
#include <unordered_set>
#include <list>
#include <deque>
#include <vector>
#include <chrono>
#include <iostream>

int main()
{
    std::list<int> nombreParticules;
    nombreParticules.push_back(64);
    nombreParticules.push_back(128);
    nombreParticules.push_back(2048);
    nombreParticules.push_back(4096);
    nombreParticules.push_back(10000);
    nombreParticules.push_back(100000);
    nombreParticules.push_back(1000000);

    std::list<Particule> listParticles;
    std::deque<Particule> dequePartices;
    std::vector<Particule> vectorParticles;
    std::unordered_set<Particule, Particule::HashParticule> setParticles;

    for (int nombreParticule : nombreParticules)
    {
        listParticles.resize(0, Particule(Vecteur(0, 0), 0.0, 0, 0, Vecteur(0, 0)));
        dequePartices.resize(0, Particule(Vecteur(0, 0), 0.0, 0, 0, Vecteur(0, 0)));
        vectorParticles.resize(0, Particule(Vecteur(0, 0), 0.0, 0, 0, Vecteur(0, 0)));
        setParticles.clear();
        auto start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
        for (int i = 0; i < nombreParticule; i++)
            listParticles.push_back(creerParticule(Vecteur(), Vecteur(1, 1, 1), i, i));
        auto end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
        auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();
        std::cout << "durée insertion de " << nombreParticule << " particules dans une liste : " << duration_sec << " s" << std::endl;

        start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
        for (int i = 0; i < nombreParticule; i++)
            vectorParticles.push_back(creerParticule(Vecteur(), Vecteur(1, 1, 1), i, i));
        end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
        duration_sec = std::chrono::duration<double>(end_time - start_time).count();
        std::cout << "durée insertion de " << nombreParticule << " particules dans un vector : " << duration_sec << " s" << std::endl;

        start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
        for (int i = 0; i < nombreParticule; i++)
            setParticles.insert(creerParticule(Vecteur(), Vecteur(1, 1, 1), i, i));
        end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
        duration_sec = std::chrono::duration<double>(end_time - start_time).count();
        std::cout << "durée insertion de " << nombreParticule << " particules dans un set : " << duration_sec << " s" << std::endl;

        start_time = std::chrono::high_resolution_clock::now(); // début du chronomètre
        for (int i = 0; i < nombreParticule; i++)
            dequePartices.push_back(creerParticule(Vecteur(), Vecteur(1, 1, 1), i, i));
        end_time = std::chrono::high_resolution_clock::now(); // fin du chronomètre
        duration_sec = std::chrono::duration<double>(end_time - start_time).count();
        std::cout << "durée insertion de " << nombreParticule << " particules dans un deque : " << duration_sec << " s" << std::endl;
    }
}