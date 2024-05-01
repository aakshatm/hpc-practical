#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void monteCarlo(int N, int K)
{
    double x, y, d;
    int pCircle = 0;
    int pSquare = 0;
    int i = 0;
#pragma omp parallel firstprivate(x, y, d, i) reduction(+ : pCircle,
pSquare) num_threads(K)
{
    srand((int)time(NULL) ^ omp_get_thread_num());
    for (i = 0; i < N; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        d = ((x * x) + (y * y));
        if (d <= 1)
        {
            pCircle++;
        }
        pSquare++;
    }
}
double pi = 4.0 * ((double)pCircle / (double)(pSquare));
printf("Final Estimation of Pi = %f\n", pi);
}
int main()
{
    int N = 2000000;
    int K = 10;
    monteCarlo(N, K);
    return 0;
}
