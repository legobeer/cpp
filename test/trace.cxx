/// Code élémentaire pour le calcul de la trace d'une matrice.
/// Printemps 2022
/// Objectif : manipuler les éléments de base du C++
///            utiliser des outils de profiling et de débogage
/// ref: l'exercice est inspiré très largement de ressources WWW

#include <cstdlib>
#include <cmath>
#include <iostream>

double *initialization(int);
void fill_matrix(double *, int);
void print_matrix(double *, int);
double trace(double *, int);

/// Driver principal pour le calcul de la tace d'une matrice
int main()
{
  int n;
  double *matrix;
  double sum;

  std::cout << std::endl
            << "Enter the Dimension for a square matrix: " << std::flush;
  std::cin >> n;
  int matrix_dim = n * n;
  matrix = initialization(matrix_dim);
  fill_matrix(matrix, matrix_dim);
  sum = trace(matrix, n);
  print_matrix(matrix, n);
  std::cout << std::endl
            << "Sum of the diagonal elements are: " << sum << std::endl;
  return 0;
}

/// @brief Routine d'initialization qui permet d'allouer la mémoire pour une
///        matrice carrée de taille n et renvoie un pointer vers
///        la matrice allouée
/// @param[in] matrix_dim est la taille totale de la matrice
/// @return    Renvoie le pointeur vers la matrice allouée
double *initialization(int matrix_dim)
{
  double *matrix;
  matrix = (double *)calloc(matrix_dim, sizeof(double *));
  return (matrix);
}

/// @brief Intitialise la matrice avec des valeurs aléatoires comprises
///        entre dans l'intervalle [-10;10]
/// @param[in] vec est le vecteur à initialiser
/// @param[in] matrix_dim   est la taille totale de la matrice 1D à initialiser
/// @return    Renvoie la matrice 1D initialisée.
void fill_matrix(double *matrix, int matrix_dim)
{
  int i;
  for (i = 0; i < matrix_dim; ++i)
    matrix[i] = rand() % 20 - 10;
}

/// @brief Affiche les éléments d'une matrice de taille n
/// @param[in] matrix est la matrice à afficher
/// @param[in] n est la taille de la matrice 1D à afficher
void print_matrix(double *matrix, int n)
{
  int i, j;
  int k = 0;

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      std::cout << matrix[k] << ", ";
      k++;
    }
    std::cout << std::endl;
  }
}

/// @brief Calcul la trace d'une matrice
/// @param[in] matrix est la matrice dont on souhaite connaître la trace.
/// @param[in] n est la taille de la matrice.
double trace(double *matrix, int n)
{
  int i;
  int k = 0;

  double sum = 0.0;
  for (i = 0; i < n; i++)
  {
    sum += matrix[k];
    k += n + 1;
  }
  return sum;
}
