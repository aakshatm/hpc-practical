#include <stdio.h>
#include <omp.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int start, int end)
{
    // Declaration
    int pivot = arr[end];
    int i = (start - 1);
    // Rearranging the array
    for (int j = start; j <= end - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    // Returning the respective index
    return (i + 1);
}

void quicksort(int arr[], int start, int end)
{
    // Declaration
    int index;
    if (start < end)
    {
        index = partition(arr, start, end);
// parallel sections
#pragma omp parallel sections
        {
#pragma omp section
            {
                // Evaluating the left half
                quicksort(arr, start, index - 1);
            }
#pragma omp section
            {
                quicksort(arr, index + 1, end);
            }
        }
    }
}

int main()
{
    // Declaration
    int N;
    printf("Enter the number of elements you want to Enter\n");
    scanf("%d", &N);
    int arr[N];
    printf("Enter the array: \n");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    quicksort(arr, 0, N - 1);
    printf("Array after Sorting is: \n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
