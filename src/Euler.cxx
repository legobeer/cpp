#include <cstdlib>
#include <cmath>
#include <iostream>

double *euler_explicite(int, int, double (*)(double, double), double, double);

double phi1(double, double);

double phi1(double, double, double);

double phi2(double, double);

double *euler_implicite(int, int, double (*)(double, double, double), double, double);

int main()
{
    double *res1 = euler_explicite(100, 1, &phi1, 0, 1);

    for (int i = 0; i < 100; i++)
    {
        std::cout << res1[i] << std::endl;
    }

    double *res2 = euler_implicite(100, 1, &phi1, 0, 1);

    for (int i = 0; i < 100; i++)
    {
        std::cout << res2[i] << std::endl;
    }

    double *res3 = euler_explicite(100, 0, &phi2, 0, 2);

    free(res1);
    free(res2);
    free(res3);
    return 0;
}

double phi1(double resU, double xValue)
{
    return 2 * resU * xValue;
}

double phi1(double resU, double xValue, double pas)
{
    return (double)resU / (1 - 2 * xValue * pas);
}

double phi2(double resU, double xValue)
{
    return 50 * resU * cos(xValue);
}

double *euler_explicite(int nbIterations, int condInitiale, double (*func)(double, double), double borneInf, double borneSup)
{
    double *res = (double *)malloc(nbIterations * sizeof(double));
    double pas = (double)(borneSup - borneInf) / (nbIterations - 1);
    double tmpX = borneInf + pas;
    res[0] = condInitiale;
    for (int i = 1; i < nbIterations; i++)
    {
        res[i] = res[i - 1] + pas * func(res[i - 1], tmpX);
        tmpX += pas;
    }
    return res;
}

double *euler_implicite(int nbIterations, int condInitiale, double (*func)(double, double, double), double borneInf, double borneSup)
{
    double *res = (double *)malloc(nbIterations * sizeof(double));
    double pas = (double)(borneSup - borneInf) / (nbIterations - 1);
    double tmpX = borneInf + pas;
    res[0] = condInitiale;
    for (int i = 1; i < nbIterations; i++)
    {
        tmpX += pas;
        res[i] = phi1(res[i - 1], tmpX, pas);
    }
    return res;
}
