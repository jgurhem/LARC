#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double *genMat(int nbRow, int nbCol) {

  double *mat;
  int i, j;

  mat = (double *)malloc(nbCol * nbRow * sizeof(double));

  for (i = 0; i < nbRow; i++)
    for (j = 0; j < nbCol; j++)
      mat[i * nbCol + j] = 100.0 * rand() / RAND_MAX;

  return mat;
}

double *extractU(double *in, int nbRow, int nbCol) {

  double *mat;
  int i, j;

  mat = (double *)malloc(nbCol * nbRow * sizeof(double));

  for (i = 0; i < nbRow; i++)
    for (j = 0; j < nbCol; j++)
      if (i <= j)
        mat[i * nbCol + j] = in[i * nbCol + j];
      else
        mat[i * nbCol + j] = 0;

  return mat;
}

double *extractL(double *in, int nbRow, int nbCol) {

  double *mat;
  int i, j;

  mat = (double *)malloc(nbCol * nbRow * sizeof(double));

  for (i = 0; i < nbRow; i++)
    for (j = 0; j < nbCol; j++)
      if (i > j)
        mat[i * nbCol + j] = in[i * nbCol + j];
      else if (i == j)
        mat[i * nbCol + j] = 1;
      else
        mat[i * nbCol + j] = 0;

  return mat;
}

void printMatrix(double *mat, int nbRow, int nbCol) {
  int i, j, max_p = 1, log_r;
  for (i = 0; i < nbRow * nbCol; i++) {
    log_r = log10(fabs(mat[i])) + 1;
    if (log_r > max_p) {
      max_p = log_r;
    }
  }
  for (i = 0; i < nbRow; i++) {
    for (j = 0; j < nbCol; j++) {
      // 5 = 1 (.) + 3 (precision) + 1 (space)
      printf("% *.3lf  ", max_p + 5, mat[i * nbCol + j]);
    }
    printf("\n");
  }
}

void printMatrixCompact(double *mat, int nbRow, int nbCol) {
  int i, j;
  for (i = 0; i < nbRow; i++) {
    for (j = 0; j < nbCol; j++) {
      printf("%5.2lf ", mat[i * nbCol + j]);
    }
    printf("\n");
  }
}

void printMatrixU(double *mat, int nbRow, int nbCol) {
  int i, j;
  for (i = 0; i < nbRow; i++) {
    for (j = 0; j < nbCol; j++) {
      if (i <= j)
        printf("%lf\t", mat[i * nbCol + j]);
      else
        printf("%lf\t", 0.0);
    }
    printf("\n");
  }
}

void printMatrixL(double *mat, int nbRow, int nbCol) {
  int i, j;
  for (i = 0; i < nbRow; i++) {
    for (j = 0; j < nbCol; j++) {
      if (i > j)
        printf("%lf\t", mat[i * nbCol + j]);
      else if (i == j)
        printf("%lf\t", 1.0);
      else
        printf("%lf\t", 0.0);
    }
    printf("\n");
  }
}
