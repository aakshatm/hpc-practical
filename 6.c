#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int nthreads, tid;
// Beginning of parallel region
#pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num();
        printf("Hello World... from thread = %d\n",
               tid);
        if (tid == 0)
        {
            // Only master thread does this
            nthreads = omp_get_num_threads();
            printf("Total number of threads = %d\n",
                   nthreads);
        }
    }
}