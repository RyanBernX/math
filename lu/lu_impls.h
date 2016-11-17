#ifndef __LU_IMPLS_H_
#define __LU_IMPLS_H_

#ifdef __cplusplus
extern "C" {
#endif

int rb_dgetrf(int, int, double *, int, int *);
void rb_dscal(int, double, double *, int);
void rb_dswap(int, double *, int, double *, int);
void rb_daxpy(int, double, const double *, int, double *, int);
int rb_idamax(int, double *, int);

#ifdef __cplusplus
}
#endif

#endif
