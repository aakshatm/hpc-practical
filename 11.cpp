#include <iostream>
#include <mpi.h>
#include <chrono>
#define N 400
using namespace std;
using namespace std::chrono;
void print_mat(double mat[][N])
{
    // printf("\nMatrix B\n\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.0f , ", mat[i][j]);
        }
        printf("\n");
    }
}
double A[N][N], B[N][N], C[N][N];
MPI_Status status;
int main(int argc, char **argv)
{
    int size, rank, slaveTaskCount, source, dest, rows, offset;
    // MPI environment is initialized
    MPI_Init(&argc, &argv);
    // Each process gets a unique ID (rank)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Number of processes in the communicator will be assigned to variable -> size
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    slaveTaskCount = size - 1;
    // MASTER
    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }
        printf("\t\tMatrix - Matrix Multiplication using MPI\n");
        // printf("\nMatrix A\n\n");
        // print_mat(A);
        // printf("\nMatrix B\n\n");
        // print_mat(B);
        // Determine the number of rows of the Matrix A, that is sent to each slave process
        // Offset variable determines the starting point of the row
        auto start = high_resolution_clock::now();
        rows = N / slaveTaskCount;
        offset = 0;
        // dividing the matrix A and sending to processes other than 0
        for (dest = 1; dest <= slaveTaskCount; dest++)
        {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&A[offset][0], rows * N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            // Matrix B is sent
            MPI_Send(&B, N * N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            offset = offset + rows;
        }
        // Root process waits until each slave process sends its calculated result with message tag 2
        for (int i = 1; i <= slaveTaskCount; i++)
        {
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            // Calculated rows of each process will be stored in Matrix C according to
            // their offset and the processed number of rows
            MPI_Recv(&C[offset][0], rows * N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
        }
        // printf("\nResult Matrix C = Matrix A * Matrix B:\n\n");
        // printf("\nMatrix C\\n\n");
        // print_mat(C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "\t***Time taken by function: "
             << duration.count() << " milliseconds***\n\n"
             << endl;
    }
    // Slave Processes
    if (rank > 0)
    {
        source = 0;
        // Slave Processes receive data from the root process with tag 1
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&A, rows * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&B, N * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        // Matrix Multiplication
        for (int k = 0; k < N; k++)
        {
            for (int i = 0; i < rows; i++)
            {
                C[i][k] = 0.0;
                for (int j = 0; j < N; j++)
                    C[i][k] = C[i][k] + A[i][j] * B[j][k];
            }
        }
        // Calculated result will be sent back to the Root process (process 0)
        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&C, rows * N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}