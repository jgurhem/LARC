#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *readCOO(char *filePath, int nbRow, int nbCol) {
  FILE *f;
  f = fopen(filePath, "r");
  if (f == NULL) {
    printf("Cannot open file %s\n", filePath);
    exit(1);
  }
  double *mat, tmp;
  mat = (double *)malloc(nbCol * nbRow * sizeof(double));
  int i, j, indI, indJ;

  for (i = 0; i < nbRow; i++) {   // row
    for (j = 0; j < nbCol; j++) { // col
      fscanf(f, "%d %d %lf", &indI, &indJ, &tmp);
      mat[indI * nbCol + indJ] = tmp;
      // printf("i-%d j-%d indi-%d indj-%d %lf \n",i,j,indI,indJ,tmp);
    }
    // printf("\n");
  }
  fclose(f);

  return mat;
}

double *readBin(char *filePath, int nbRow, int nbCol) {
  FILE *f;
  f = fopen(filePath, "r");
  if (f == NULL) {
    printf("Cannot open file %s\n", filePath);
    exit(1);
  }
  double *mat;
  mat = (double *)malloc(nbCol * nbRow * sizeof(double));
  fread(mat, sizeof(double), nbCol * nbRow, f);
  fclose(f);

  return mat;
}

void genMatrixBlockBinR(char *filePath, char *sep, int nb, int bsize,
                        double *mat, int blockRow, int blockCol) {
  FILE *f;
  char matPath[150];
  sprintf(matPath, "%s%d%s%d", filePath, blockRow, sep, blockCol);
  f = fopen(matPath, "r");
  if (f == NULL) {
    printf("Cannot open file %s\n", matPath);
    exit(1);
  }

  int i;

  for (i = 0; i < bsize; i++) { // row
    fread(mat + (blockRow * bsize + i) * nb * bsize + blockCol * bsize,
          sizeof(double), bsize, f);
  }
  fclose(f);
}

void genMatrixBlock(char *filePath, char *sep, int nb, int bsize, double *mat,
                    int blockRow, int blockCol) {
  FILE *f;
  char matPath[150];
  sprintf(matPath, "%s%d%s%d", filePath, blockRow, sep, blockCol);
  f = fopen(matPath, "r");
  if (f == NULL) {
    printf("Cannot open file %s\n", matPath);
    exit(1);
  }

  int i, j, indI, indJ;
  double tmp;

  for (i = 0; i < bsize; i++) {   // row
    for (j = 0; j < bsize; j++) { // col
      // fscanf(f,"%lf",&tmp);
      fscanf(f, "%d %d %lf", &indI, &indJ, &tmp);
      // mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = tmp;
      mat[(blockRow * bsize + indI) * nb * bsize + blockCol * bsize + indJ] =
          tmp;
      // printf("i-%d j-%d indi-%d indj-%d %lf \n",i,j,indI,indJ,tmp);
    }
    // printf("\n");
  }
  fclose(f);
}

void genBlockUnit(int nb, int bsize, double *mat, int blockRow, int blockCol) {

  int i, j;

  for (i = 0; i < bsize; i++) {   // row
    for (j = 0; j < bsize; j++) { // col
      if (j == i)
        mat[(blockRow * bsize + i) * nb * bsize + blockCol * bsize + j] = 1;
      else
        mat[(blockRow * bsize + i) * nb * bsize + blockCol * bsize + j] = 0;
    }
  }
}

void genBlockZero(int nb, int bsize, double *mat, int blockRow, int blockCol) {

  int i, j;

  for (i = 0; i < bsize; i++) {   // row
    for (j = 0; j < bsize; j++) { // col
      mat[(blockRow * bsize + i) * nb * bsize + blockCol * bsize + j] = 0;
    }
  }
}

void extractBlock(int nb, int bsize, double *src, double *dst, int blockRow,
                  int blockCol) {

  int i, j;

  for (i = 0; i < bsize; i++) {   // row
    for (j = 0; j < bsize; j++) { // col
      dst[(blockRow * bsize + i) * nb * bsize + blockCol * bsize + j] =
          src[(blockRow * bsize + i) * nb * bsize + blockCol * bsize + j];
    }
  }
}

double *readBlockMatrixBinR(char *filePath, char *sep, int nb, int bsize) {

  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      genMatrixBlockBinR(filePath, sep, nb, bsize, mat, i, j);
    }
  }

  return mat;
}

double *readBlockMatrixCOO(char *filePath, char *sep, int nb, int bsize) {

  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      genMatrixBlock(filePath, sep, nb, bsize, mat, i, j);
    }
  }

  return mat;
}

double *extractMatrixU(int nb, int bsize, double *src) {
  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      if (i <= j)
        extractBlock(nb, bsize, src, mat, i, j);
      else
        genBlockZero(nb, bsize, mat, i, j);
    }
  }
  return mat;
}

double *genMatrixU(char *filePath, int nb, int bsize) {

  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      if (i <= j)
        genMatrixBlock(filePath, ",", nb, bsize, mat, i, j);
      else
        genBlockZero(nb, bsize, mat, i, j);
    }
  }

  return mat;
}

double *extractMatrixL(int nb, int bsize, double *src) {
  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      if (i > j)
        extractBlock(nb, bsize, src, mat, i, j);
      else if (i == j)
        genBlockUnit(nb, bsize, mat, i, j);
      else
        genBlockZero(nb, bsize, mat, i, j);
    }
  }
  return mat;
}

double *genMatrixL(char *filePath, int nb, int bsize) {

  double *mat;
  int i, j;
  mat = (double *)malloc(nb * nb * bsize * bsize * sizeof(double));
  for (i = 0; i < nb; i++) {
    for (j = 0; j < nb; j++) {
      if (i > j)
        genMatrixBlock(filePath, ",", nb, bsize, mat, i, j);
      else if (i == j)
        genBlockUnit(nb, bsize, mat, i, j);
      else
        genBlockZero(nb, bsize, mat, i, j);
    }
  }
  return mat;
}

void printMatrixLatex(double *mat, int nb, int bsize) {
  int i, j;
  for (i = 0; i < bsize * nb; i++) {   // row
    for (j = 0; j < bsize * nb; j++) { // col
      printf("%8.3lf", mat[i * nb * bsize + j]);
      if (j < bsize * nb - 1)
        printf(" &");
    }
    printf("\\\\\n");
  }
}

void cleanMatrix(double *mat) { free(mat); }
