#include <stdio.h>
#include <stdlib.h>

double *genVect(int nbRow) {

  double *mat;
  int i;

  mat = (double *)malloc(nbRow * sizeof(double));

  for (i = 0; i < nbRow; i++)
    mat[i] = 100.0 * rand() / RAND_MAX;

  return mat;
}
