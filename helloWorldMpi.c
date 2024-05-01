#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    
    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Print "Hello World" from each process
    printf("Hello World from process %d of %d\n", rank, size);
    
    // Finalize MPI
    MPI_Finalize();
    
    return 0;
}
