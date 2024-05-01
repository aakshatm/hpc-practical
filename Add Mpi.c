#include <stdio.h>

#include <mpi.h>

#include <stdlib.h>

#include <unistd.h>

#define ARRAY_SIZE 10
int array[] = {
  15,
  20,
  30,
  24,
  65,
  36,
  57,
  68,
  29,
  12
};
int received_array[1000];
int main(int argc, char * argv[]) {
  int process_id, num_processes, elements_per_process,
  received_elements_count;
  MPI_Status status;
  MPI_Init( & argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, & process_id);
  MPI_Comm_size(MPI_COMM_WORLD, & num_processes);
  if (process_id == 0) {
    int index, i;
    elements_per_process = ARRAY_SIZE / num_processes;
    if (num_processes > 1) {
      for (i = 1; i < num_processes - 1; i++) {
        index = i * elements_per_process;
        MPI_Send( & elements_per_process, 1, MPI_INT, i, 0,
          MPI_COMM_WORLD);
        MPI_Send( & array[index], elements_per_process, MPI_INT, i,
          0, MPI_COMM_WORLD);
      }
      index = i * elements_per_process;
      int elements_left = ARRAY_SIZE - index;
      MPI_Send( & elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send( & array[index], elements_left, MPI_INT, i, 0,
        MPI_COMM_WORLD);
    }
    int sum = 0;
    for (i = 0; i < elements_per_process; i++)
      sum += array[i];
    printf("Sum calculated by the root process: %d\n", sum);
    int tmp;
    for (i = 1; i < num_processes; i++) {
      MPI_Recv( & tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &
        status);
      int sender = status.MPI_SOURCE;
      printf("Partial sum received from process %d: %d\n", i, tmp);
      sum += tmp;
    }
    printf("Total sum of the array: %d\n", sum);
  } else {
    MPI_Recv( & received_elements_count, 1, MPI_INT, 0, 0,
      MPI_COMM_WORLD, & status);
    MPI_Recv( & received_array, received_elements_count, MPI_INT, 0, 0,
      MPI_COMM_WORLD, & status);
    int partial_sum = 0;
    for (int i = 0; i < received_elements_count; i++)
      partial_sum += received_array[i];
    MPI_Send( & partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
