#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500;

// Function to perform matrix multiplication
void multiplyMatrix(int mat1[][N], int mat2[][N], int res[][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            res[i][j] = 0;
            for (int k = 0; k < N; ++k)
            {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main()
{
    int mat1[N][N], mat2[N][N], res[N][N];

    // Initialize matrices with random values
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            mat1[i][j] = rand() % 100;
            mat2[i][j] = rand() % 100;
        }
    }

    // Start measuring time
    auto start = high_resolution_clock::now();

    // Perform matrix multiplication
    multiplyMatrix(mat1, mat2, res);

    // Stop measuring time and calculate duration
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Output the time taken
    cout << "Time taken for matrix multiplication: " << duration.count() << " milliseconds" << endl;

    return 0;
}