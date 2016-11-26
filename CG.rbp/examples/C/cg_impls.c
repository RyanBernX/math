#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cg_impls.h"
/** @file cg_impls.c
 *  @author RyanBern
 *  @brief Simple implementations of conjugate gradient method for
 *  solving linear systems.
 *
 */

/** @fn int rb_dcgsv(int n, Aop A, void *ctxt, const double *b, double *sol)
 *  @brief Solves a linear system using conjugate method.
 *  @param n The dimension of A.
 *  @param A The function pointer of type Aop.
 *  @param ctxt The context needed by A.
 *  @param b The right hand side of \f$Ax=b\f$.
 *  @param sol @a Output. The computed solution of the equation.
 *  @return The number of iterations in the conjugate method.
 *
 *  The function @a rb_dcgsv solves the linear system \f$Ax=b\f$ with conjugate
 *  gradient method. It requires \f$A\f$ to be positive definite.
 *
 *  Conjugate gradient method doesn't need the matrix \f$A\f$ to be given
 *  explicitly. It only needs \f$A\f$ when applying it to a vector. That
 *  is, the user only has to tell how to perform \f$y\leftarrow Ax\f$, by
 *  providing the parameter of type Aop and all the context needed by
 *  the operator.
 *  
 */

int rb_dcgsv(int n, Aop A, void *ctxt, const double *b, double *sol){
  int i, itr_max = 2 * n;
  double *work, alpha, beta, dAd, nrmG, *g, *d, *Ad, *Ax;

  /* allocate workspace 
     work = [g; d; Ad; Ax]*/
  work = (double*)malloc(4 * n * sizeof(double));
  g = work; d = work + n; Ad = work + 2*n; Ax = work + 3*n;

  /* initialize sol to zeros */
  for (i = 0; i < n; i++) sol[i] = 0;
  /* compute g, d = b*/
  rb_dcopy(n, b, 1, g, 1);
  rb_dcopy(n, b, 1, d, 1);

  nrmG = rb_damax(n, g, 1);

  for (i = 0; i < itr_max; i++){
    /* stop rule */
    if (nrmG < 1E-12) break;
    A(ctxt, n, d, 1, Ad, 1);

    dAd = rb_ddot(n, d, 1, Ad, 1);
    alpha = rb_ddot(n, g, 1, d, 1) / dAd;

    /* update X, g, beta, d*/
    rb_daxpy(n, alpha, d, 1, sol, 1);
    A(ctxt, n, sol, 1, Ax, 1);
    rb_dsub(n, b, 1, Ax, 1, g, 1);

    beta = -rb_ddot(n, g, 1, Ad, 1) / dAd;

    rb_dscal(n, beta, d, 1);
    rb_daxpy(n, 1, g, 1, d, 1);

    nrmG = rb_damax(n, g, 1);

  }
  if (i == itr_max)
    fprintf(stderr, "Failed to converge, nrmG at %e\n", nrmG);

  free(work);
  return i;
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

/** @fn void rb_damax(int n, const double *X, int incx)
 *  @brief Finds the element in X which has the maximum absolute
 *  value.
 *  @param n The length of X.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @return The element which has the maximum absolute value
 */

double rb_damax(int n, const double *X, int incx){
  int i;
  double t, vdm;

  if (n <= 0) return 0;

  vdm = X[0];
  for (i = 1; i < n; i++){
    t = fabs(X[i * incx]);
    if (t > vdm) vdm = t;
  }

  return vdm;
}

/** @fn double rb_ddot(int n, const double *X, int incx, const double *Y,
 *  int incy)
 *  @brief Perform inner product \f$x^Ty\f$.
 *  @param n The length of X and Y.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @param Y The pointer to the storage of Y.
 *  @param incy The increment of indices of Y.
 *  @return The inner product.
 */

double rb_ddot(int n, const double *X, int incx, const double *Y, int incy){
  int i;
  double ret = 0;

  for (i = 0; i < n; i++)
    ret += X[i * incx] * Y[i * incy];

  return ret;
}

/** @fn void rb_dcopy(int n, const double *X, int incx, double *Y,
 *  int incy)
 *  @brief Copy a vector to another.
 *  @param n The length of X and Y.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @param Y The pointer to the storage of Y.
 *  @param incy The increment of indices of Y.
 */

void rb_dcopy(int n, const double *X, int incx, double *Y, int incy){
  int i;

  for (i = 0; i < n; i++)
    Y[i * incy] = X[i * incx];

}

/** @fn void rb_dsub(int n, const double *X, int incx, const double *Y,
 *  int incy, double *Z, int incz)
 *  @brief Perform vector substraction, i.e. \f$z=x-y\f$.
 *  @param n The length of X and Y.
 *  @param X The pointer to the storage of X.
 *  @param incx The increment of indices of X.
 *  @param Y The pointer to the storage of Y.
 *  @param incy The increment of indices of Y.
 *  @param Z @a Output. The pointer to the storage of Z.
 *  @param incy The increment of indices of Z.
 */

void rb_dsub(int n, const double *X, int incx, const double *Y, int incy, \
  double *Z, int incz){
  int i;

  for (i = 0; i < n; i++)
    Z[i * incz] = X[i * incx] - Y[i * incy];

}
