#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int main() {
  int i, j, k;
  double ** a, ** b, ** c;
  clock_t start, end;
  double cpu_time_used;
  a = (double ** ) malloc(N * sizeof(double * ));
  b = (double ** ) malloc(N * sizeof(double * ));
  c = (double ** ) malloc(N * sizeof(double * ));
  for (i = 0; i < N; i++) {
    a[i] = (double * ) malloc(N * sizeof(double));
    b[i] = (double * ) malloc(N * sizeof(double));
    c[i] = (double * ) malloc(N * sizeof(double));
  }
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      a[i][j] = 1.0;
      b[i][j] = 2.0;
      c[i][j] = 0.0;
    }
  }
  // Start timer
  start = clock();
  // Multiply matrices
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  // End timer
  end = clock();
  // Calculate CPU time used
  cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
  // Print result and execution time
  printf("Multiplication of matrices of size %d x %d took %f seconds.\n",N, N, cpu_time_used);
  // Free memory
  for (i = 0; i < N; i++) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }
  free(a);
  free(b);
  free(c);
  return 0;
}
