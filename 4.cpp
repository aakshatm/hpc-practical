#include <iostream>
#include <pthread.h>
#define MAX_TERMS 100
int fib[MAX_TERMS];
int num_terms;
void *fibonacci(void *arg)
{
    int n = *((int *)arg);
    if (n == 0)
    {
        fib[0] = 0;
        pthread_exit(NULL);
    }
    if (n == 1)
    {
        fib[1] = 1;
        pthread_exit(NULL);
    }
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[MAX_TERMS];
    int terms[MAX_TERMS];
    std::cout << "Enter the number of terms in Fibonacci series: ";
    std::cin >> num_terms;
    if (num_terms > MAX_TERMS || num_terms <= 0)
    {
        std::cout << "Invalid number of terms.\n";
        return 1;
    }
    for (int i = 0; i < num_terms; i++)
    {
        terms[i] = i + 1;
        pthread_create(&threads[i], NULL, fibonacci, &terms[i]);
    }
    for (int i = 0; i < num_terms; i++)
    {
        pthread_join(threads[i], NULL);
    }
    std::cout << "Fibonacci Series Thread id: " << std::endl;
    for (int i = 0; i < num_terms; i++)
    {
        std::cout << fib[i] << " ";
        std::cout << threads[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}