#ifndef MVOPUTILS
#define MVOPUTILS

void genMatrixBlock(char * filePath, int nb, int bsize, double * mat, int blockRow, int blockCol);
double * genSingleMat(char * filePath, int nbRow, int nbCol);

double * genMatrixA(char* filePath, int nb, int bsize);
double * genMatrixL(char* filePath, int nb, int bsize);
double * genMatrixU(char* filePath, int nb, int bsize);

double * extractMatrixL(int nb, int bsize, double *src);
double * extractMatrixU(int nb, int bsize, double *src);

void printMatrixLatex(double *mat, int nb, int bsize);
void cleanMatrix(double *mat);

double* genVector(char* filePath, int nb, int bsize);
double * genSingleVect(char * filePath, int bsize);

void printVector(double *mat, int nb, int bsize);
void printVectorLatex(double *mat, int nb, int bsize);
void cleanVector(double *mat);

double * genMat(int nbRow, int nbCol);
double * extractU(double *in, int nbRow, int);
double * extractL(double *in, int nbRow, int);
void printMatrix(double *mat, int nbRow, int nbCol);
void printMatrixU(double *mat, int nbRow, int nbCol);
void printMatrixL(double *mat, int nbRow, int nbCol);

double * genVect(int nbRow);
void printVect(double *mat, int nbRow);

double* dgeaxpxmv(double *A, double *x, int size);
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

double dot(double *A, double *B, int size);
double normEuclidean(double *A, int size);
double powerIt(double *A, double *b, int size, double epsilon, int itmax);
#endif
