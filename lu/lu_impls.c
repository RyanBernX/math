#include <stdio.h>
#include <math.h>
#include "lu_impls.h"
/** @file lu_impls.c
 *  @author RyanBern
 *  @brief Simple implementations of PLU factorization
 *
 */

/** @fn int rb_dgetrf(int m, int n, double *A, int lda, int *ipiv)
 *  @brief Computes the PLU factorization of an m by n matrix A, i.e.
 *  \f$ PA=LU \f$
 *  @param m The number of rows of A.
 *  @param n The number of columns of A.
 *  @param A @a Input/Output. Pointer to the storage of A.
 *  @param lda The leading dimension of A.
 *  @param ipiv @a Output. The integer array that stores the pivoting indices.
 *  That is, row i exchanges with row ipiv[i].
 *  @return The function returns 0 when it exits normally. When it returns with
 *  a positive integer i, it means that lu stops at i-th row because A may
 *  be singular or ill-conditioned.
 *
 *  On exit, R is stored at the upper triangular/trapezoidal part of A,
 *           L is stored at the strictly lower triangular/trapezoidal
 *           part of A, the diagonal of L is not stored.
 *  
 *  For example, suppose A is 4 by 3
 *  \f[ A = \left(\begin{array}{ccc}
 *  a_{11} & a_{12} & a_{13} \\
 *  a_{21} & a_{22} & a_{23} \\
 *  a_{31} & a_{32} & a_{33} \\
 *  a_{41} & a_{42} & a_{43} \\
 *  \end{array}\right)
 *  \f]
 *  Then after LU is completed, A is overwritten by
 *  \f[ A = \left(\begin{array}{ccc}
 *  u_{11} & u_{12} & u_{13} \\
 *  l_{21} & u_{22} & u_{23} \\
 *  l_{31} & l_{32} & u_{33} \\
 *  l_{41} & l_{42} & l_{43} \\
 *  \end{array}\right)
 *  \f]
 */

int rb_dgetrf(int m, int n, double *A, int lda, int *ipiv){
  int i, j;

  for (i = 0; i < m && i < n; i++){
    ipiv[i] = i + rb_idamax(m - i, A + i * lda + i, 1);
    if (ipiv[i] != i)
      rb_dswap(n - i, A + i * lda + i, lda, A + i * lda + ipiv[i], lda);

    if (A[i * lda + i] == 0) return i;

    for (j = i + 1; j < m; j++){
      A[i * lda + j] /= A[i * lda + i];
      rb_daxpy(n - i - 1, -A[i * lda + j], A + (i + 1) * lda + i, lda,\
        A + (i + 1)* lda + j, lda);
    }
  }
  return 0;
}

/** @fn void rb_dscal(int n, double a, double *X, int incx)
 *  @brief Scales a vector by a constant. \f$x\leftarrow ax\f$
 *  @param n The length of X.
 *  @param a The scaling factor.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices.
 *
 */ 

void rb_dscal(int n, double a, double *X, int incx){
  int i;

  for (i = 0; i < n; i++)
    X[i * incx] *= a;
}

/** @fn void rb_dswap(int n, double *X, int incx, double *Y, int incy)
 *  @brief Swaps the value of vector X and Y.
 *  @param n The length of X and Y.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @param Y The pointer to the storage of Y.
 *  @param incy The increment of indices of Y.
 */

void rb_dswap(int n, double *X, int incx, double *Y, int incy){
  int i, ix, iy;
  double t;

  for (i = 0; i < n; i++){
    ix = i * incx; iy = i * incy;
    t = X[ix]; X[ix] = Y[iy]; Y[iy] = t;
  }
}

/** @fn void rb_daxpy(int n, double a, const double *X, int incx, double *Y,
 *  int incy)
 *  @brief Scale a vector X by a constant add add it to another vector Y.
 *  \f$y\leftarrow y+ax\f$
 *  @param n The length of X and Y.
 *  @param a The scaling constant.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @param Y @a Input/Output. The pointer to the storage of Y.
 *  @param incy The increment of indices of Y.
 */

void rb_daxpy(int n, double a, const double *X, int incx, \
  double *Y, int incy){

  int i;

  for (i = 0; i < n; i++)
    Y[i * incy] += a * X[i * incx];
}

/** @fn int rb_idamax(int n, double *X, int incx)
 *  @brief Finds the index of the element in X which has the maximum absolute
 *  value.
 *  @param n The length of X.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 */

int rb_idamax(int n, double *X, int incx){
  int idm, i;
  int vdm;
  double t;

  if (n <= 0) return 0;

  idm = 0; vdm = X[0];
  for (i = 1; i < n; i++){
    t = fabs(X[i * incx]);
    if (t > vdm){
      vdm = t; idm = i;
    }
  }

  return idm;
}
