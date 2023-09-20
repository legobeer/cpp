#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

double phi1(double resU, double xValue)
{
    return 2 * resU * xValue;
}

double phi1(double resU, double xValue, double pas)
{
    return resU / (1 - 2 * xValue * pas);
}

double phi2(double resU, double xValue)
{
    return 50 * resU * cos(xValue);
}

std::vector<double> euler_explicite(int nbIterations, int condInitiale, double (*func)(double, double), double borneInf, double borneSup)
{
    std::vector<double> res(0, nbIterations);
    double pas = (borneSup - borneInf) / (nbIterations - 1);
    double tmpX = borneInf + pas;
    res[0] = condInitiale;
    for (int i = 1; i < nbIterations; i++)
    {
        res[i] = res[i - 1] + pas * func(res[i - 1], tmpX);
        tmpX += pas;
    }
    return res;
}

std::vector<double> euler_implicite(int nbIterations, int condInitiale, double (*func)(double, double, double), double borneInf, double borneSup)
{
    std::vector<double> res(0, nbIterations);
    double pas = (borneSup - borneInf) / (nbIterations - 1);
    double tmpX = borneInf + pas;
    res[0] = condInitiale;
    for (int i = 1; i < nbIterations; i++)
    {
        tmpX += pas;
        res[i] = phi1(res[i - 1], tmpX, pas);
    }
    return res;
}
