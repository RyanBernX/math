#ifndef __CG_IMPLS_H_
#define __CG_IMPLS_H_

/** @file cg_impls.h
 *  @brief Headers for function prototypes and typedefs.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @var typedef void (*Aop)(void *, int, const double *, int, double *, int);
 *  @brief The prototype of all matrix-vector operators. It requires six
 *  parameters and has no return value.
 *  @param ctxt Type void*. All necessary contexts needed by the operator. 
 *  @param n Type int. the length of X and Y.
 *  @param X Type const double*. The pointer to the storage of X.
 *  @param incx Type int. The increment of indices of X.
 *  @param Y Type double*. @a Input/Output. The pointer to the storage of Y.
 *  @param incy Type int. The increment of indices of Y.
 *  
 */
typedef void (*Aop)(void *, int, const double *, int, double *, int);

int rb_dcgsv(int, Aop, void *, const double *, double *);
void rb_dscal(int, double, double *, int);
void rb_daxpy(int, double, const double *, int, double *, int);
double rb_damax(int, const double *, int);
double rb_ddot(int, const double *, int, const double *, int);
void rb_dsub(int, const double *, int, const double *, int, \
  double *, int);
void rb_dcopy(int, const double *, int, double *, int);


#ifdef __cplusplus
}
#endif

#endif
