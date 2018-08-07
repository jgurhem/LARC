#ifndef MATRIXUTILS
#define MATRIXUTILS

double * genMat(int nbRow, int nbCol);
double * extractU(double *in, int nbRow, int);
double * extractL(double *in, int nbRow, int);
void printMatrix(double *mat, int nbRow, int nbCol);
void printMatrixU(double *mat, int nbRow, int nbCol);
void printMatrixL(double *mat, int nbRow, int nbCol);

#endif
