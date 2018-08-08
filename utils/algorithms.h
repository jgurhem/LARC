#ifndef ALGORITHMS
#define ALGORITHMS

void prodDiff(double*A, double*B, double*C,int size);
void prodMatVect(double*A, double*x, double*y,int size);
void prodMat(double*A, double*B, int size);
double* mProdMat(double*A, double*B, int size);

double * inversion(double*A, int size);
void factLU(double* A, int size);
void factLU2(double* A, int size);

void solveLinearSystem(double *A, double *b, int size);
void gaussElimination(double *A, double *B, int size);
void gaussElimination2(double *A, double *B, int size);
void gaussElimination3(double *A, double *B, int size);
void gaussElimination4(double *A, double *B, int size);
void gaussJordan(double *A, double *B, int size);

double diffNorm(double *A, double *B, int size);
#endif
