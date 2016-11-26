#include <stdio.h>
#include <stdlib.h>
#include "cg_impls.h"

#define N1 40
#define N2 60000

void rb_vec_print(int, const double *, int);

void hilbert_Ax(void *, int, const double *, int, double *, int);
void tridiag_Ax(void *, int, const double *, int, double *, int);

int main(int argc, char **argv){
  int i, j, itr;
  double *b, *x, A[] = {10, 1};

  /* generate test data for problem #1*/
  b = (double*)calloc(N1, sizeof(double));
  x = (double*)calloc(N1, sizeof(double));
  for (i = 0; i < N1; i++)
    for (j = 0; j < N1; j++)
      b[i] += 1.0 / (i + j + 1);

  /* call conjugate gradient */
  itr = rb_dcgsv(N1, hilbert_Ax, NULL, b, x);

  /* show the results */
  printf("converges in %d steps.\n", itr);
  rb_vec_print(N1, x, 1);

  /* free */
  free(b); free(x);

  /* generate test data for problem #2*/
  b = (double*)calloc(N2, sizeof(double));
  x = (double*)calloc(N2, sizeof(double));
  for (i = 1; i < N2 - 1; i++) b[i] = 12;
  b[0] = b[N2 - 1] = 11;

  /* call conjugate gradient */
  itr = rb_dcgsv(N2, tridiag_Ax, A, b, x);

  /* show the results */
  printf("converges in %d steps.\n", itr);
  rb_vec_print(N2, x, 1);

  /* free */
  free(b); free(x);
  return 0; 
}


void rb_vec_print(int n, const double *X, int incx){
  int i;

  for (i = 0; i < n; i++)
    printf("[%d]\t%5.4e\n", i + 1, X[i * incx]);

}

void hilbert_Ax(void *A, int n, const double *x, int incx, \
  double *y, int incy){

  int i, j;
  for (i = 0; i < n; i++){
    y[i * incy] = 0;
    for (j = 0; j < n; j++)
      y[i * incy] += x[j * incx] / (i + j + 1);
  }
}

void tridiag_Ax(void *A, int n, const double *x, int incx, \
  double *y, int incy){

  int i;
  double *data = (double*)A, d = data[0], o = data[1];

  if (n <= 0) return;
  if (n == 1){
    y[0] = d * x[0];
    return;
  }

  y[0] = d * x[0] + o * x[incx];
  y[(n - 1) * incy] = d * x[(n - 1) * incx] + o * x[(n - 2) * incx];

  for (i = 1; i < n - 1; i++)
    y[i * incy] = d * x[i * incx] + o * (x[(i - 1) * incx] + x[i + 1] * incx);

}
