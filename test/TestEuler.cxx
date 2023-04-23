#include "Euler.hxx"
#include <iostream>

int main()
{
    double *res1 = euler_explicite(100, 1, &phi1, 0, 1);

    double count = 0;

    double *res2 = euler_implicite(100, 1, &phi1, 0, 1);

    double *res3 = euler_explicite(100, 0, &phi2, 0, 2);

    count = 0;

    for (int i = 0; i < 100; i++)
    {
        std::cout << count << " " << res3[i] << std::endl;
        count += 0.02;
    }

    free(res1);
    free(res2);
    free(res3);
    return 0;
}