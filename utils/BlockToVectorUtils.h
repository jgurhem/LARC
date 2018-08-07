#ifndef BLOCKTOVECTORUTILS
#define BLOCKTOVECTORUTILS

double* genVector(char* filePath, int nb, int bsize);
double * genSingleVect(char * filePath, int bsize);

void printVector(double *mat, int nb, int bsize);
void printVectorLatex(double *mat, int nb, int bsize);
void cleanVector(double *mat);

#endif
