#ifndef BLOCKTOMATRIXUTILS
#define BLOCKTOMATRIXUTILS

void genMatrixBlock(char * filePath, int nb, int bsize, double * mat, int blockRow, int blockCol);
double * genSingleMat(char * filePath, int nbRow, int nbCol);

double * genMatrixA(char* filePath, int nb, int bsize);
double * genMatrixL(char* filePath, int nb, int bsize);
double * genMatrixU(char* filePath, int nb, int bsize);

double * extractMatrixL(int nb, int bsize, double *src);
double * extractMatrixU(int nb, int bsize, double *src);

void printMatrixLatex(double *mat, int nb, int bsize);
void cleanMatrix(double *mat);

#endif
