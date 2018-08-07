#ifndef BLOCKTOMATRIXUTILS
#define BLOCKTOMATRIXUTILS

void genMatrixBlock(char * filePath, int nb, int bsize, double * mat, int blockRow, int blockCol);
double * genSingleMat(char * filePath, int bsize);

double * genMatrixA(char* filePath, int nb, int bsize);
double * genMatrixL(char* filePath, int nb, int bsize);
double * genMatrixU(char* filePath, int nb, int bsize);

double * extractU(double *in, int nbRow, int);
double * extractL(double *in, int nbRow, int);

void printMatrix(double *mat, int nb, int bsize);
void printMatrixLatex(double *mat, int nb, int bsize);
void cleanMatrix(double *mat);

#endif
