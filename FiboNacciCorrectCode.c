#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define MAX_SIZE 1000
// Global variables
int n;
double golden_ratio = 1.618034;
double igolden_ratio = 1 - 1.618034;
// double temp = 5;
double sqrt5 = 2.2360;
double fib[MAX_SIZE];
// Function to calculate Fibonacci sequence using the golden ratio formula
void calculate_fib(int start)
{
    printf("Thread %ld calculating fib from %d to %d\n", pthread_self(),
           start, start + (n / 4) - 1);
    int end = start + (n / 4);
    if (end > n - 4)
        end = n;
    for (int i = start; i < end; i++)
    {
        double fib_double = (pow(golden_ratio, i) - pow(igolden_ratio, i)) / sqrt5;
        fib[i] = fib_double;
    }
}
// Thread function
void *thread_func(void *arg)
{
    int start = *((int *)arg);
    calculate_fib(start);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[4];
    int thread_args[4];
    // Input n from the user
    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);
    // Divide n by 4 for each thread
    int interval = n / 4;
    // Create threads
    for (int i = 0; i < 4; i++)
    {
        thread_args[i] = i * interval + 1;
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }
    // Join threads
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
    // Print the Fibonacci array
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.0f ", fib[i]);
    }
    printf("\n");
    return 0;
}
