#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int *prime_table(int prime_num);
double *sine_table(int sine_num);
void timestamp();

int main(void)
{
    int prime_num;
    int *primes;
    int sine_num;
    double *sines;
    double wtime;
    double wtime1;
    double wtime2;
    timestamp();
    printf("\n");
    printf("MULTITASK_OPENMP:\n");
    printf(" C/OpenMP version\n");
    printf(" Demonstrate how OpenMP can \"multitask\" by using the\n");
    printf(" SECTIONS directive to carry out several tasks in parallel.\n");
    prime_num = 20000;
    sine_num = 20000;
    wtime = omp_get_wtime();
#pragma omp parallel shared(prime_num, primes, sine_num, sines)
    {
#pragma omp sections
        {
#pragma omp section
            {
                wtime1 = omp_get_wtime();
                primes = prime_table(prime_num);
                wtime1 = omp_get_wtime() - wtime1;
            }
#pragma omp section
            {
                wtime2 = omp_get_wtime();
                sines = sine_table(sine_num);
                wtime2 = omp_get_wtime() - wtime2;
            }
        }
    }
    wtime = omp_get_wtime() - wtime;
    printf("\n");
    printf(" Number of primes computed was %d\n", prime_num);
    printf(" Last prime was %d\n", primes[prime_num - 1]);
    printf(" Number of sines computed was %d\n", sine_num);
    printf(" Last sine computed was %f\n", sines[sine_num - 1]);
    printf("\n");
    printf(" Elapsed time = %f\n", wtime);
    printf(" Task 1 time = %f\n", wtime1);
    printf(" Task 2 time = %f\n", wtime2);
    free(primes);
    free(sines);
    printf("\n");
    printf("MULTITASK_OPENMP:\n");
    printf(" Normal end of execution.\n");
    printf("\n");
    timestamp();
    return 0;
}

int *prime_table(int prime_num)
{
    int i;
    int j;
    int p;
    int prime;
    int *primes;
    primes = (int *)malloc(prime_num * sizeof(int));
    i = 2;
    p = 0;
    while (p < prime_num)
    {
        prime = 1;
        for (j = 2; j < i; j++)
        {
            if ((i % j) == 0)
            {
                prime = 0;
                break;
            }
        }
        if (prime)
        {
            primes[p] = i;
            p = p + 1;
        }
        i = i + 1;
    }
    return primes;
}

double *sine_table(int sine_num)
{
    double a;
    int i;
    int j;
    double pi = 3.141592653589793;
    double *sines;
    sines = (double *)malloc(sine_num * sizeof(double));
    for (i = 0; i < sine_num; i++)
    {
        sines[i] = 0.0;
        for (j = 0; j <= i; j++)
        {
            a = (double)(j)*pi / (double)(sine_num - 1);
            sines[i] = sines[i] + sin(a);
        }
    }
    return sines;
}

void timestamp()
{
    const int TIME_SIZE = 40;
    char time_buffer[TIME_SIZE];
    const struct tm *tm_ptr;
    time_t now;
    now = time(NULL);
    tm_ptr = localtime(&now);
    strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    printf("%s\n", time_buffer);
    return;
}
