#include <stdio.h>
#include <stdlib.h>
#include "lu_impls.h"

void rb_mat_print(int, int, const double*, int);

int main(int argc, char **argv){
  int i, N, *ipiv;
  double *A;

  if (argc != 2){
    fprintf(stderr, "Usage: ./main.x <dim>\n");
    return 1;
  }

  N = strtol(argv[1], NULL, 10);

  /* generate test matrix */
  A = (double*)calloc(N * N, sizeof(double));
  ipiv = (int*)calloc(N, sizeof(int));

  for (i = 0; i < N; i++){
    A[i * N + i] = 6;
    if (i > 0) A[i * N + i - 1] = 1;
    if (i < N - 1) A[i * N + i + 1] = 8;
  }

  /* call lu */
  rb_dgetrf(N, N, A, N, ipiv);

  /* show the results */
  rb_mat_print(N, N, A, N);
  for (i = 0; i < N; i++)
    printf("%d\t", ipiv[i]);

  printf("\n");

  /* free */
  free(A); free(ipiv);
  return 0; 
}


void rb_mat_print(int m, int n, const double *A, int lda){
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      printf("%.3f%c", A[j * lda + i], j == n - 1 ? '\n' : '\t');

}
