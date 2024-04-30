#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    const long long num_samples = 1000000000; // Number of samples for Monte Carlo
    long long count = 0;
#pragma omp parallel reduction(+ : count)
    {
        unsigned int seed = omp_get_thread_num(); // Unique seed for each thread
#pragma omp for
        for (int i = 0; i < num_samples; ++i)
        {
            double x = ((double)rand_r(&seed) / RAND_MAX) * 2 - 1;
            double y = ((double)rand_r(&seed) / RAND_MAX) * 2 - 1;
            if (x * x + y * y <= 1.0)
                count++;
        }
    }
    double pi_estimate = 4.0 * count / num_samples;
    printf("Estimated value of pi: %.10f\n", pi_estimate);
    return 0;
}
