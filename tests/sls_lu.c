#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *v, *vc, *mc;
  int size = 5;
  m = genMat(size, size);
  v = genVect(size);

  mc = malloc(size * size * sizeof(double));
  memcpy(mc, m, size * size * sizeof(double));

  vc = malloc(size * sizeof(double));
  memcpy(vc, v, size * sizeof(double));

  printf("A\n");
  printMatrix(m, size, size);
  printf("v\n");
  printMatrix(v, size, 1);
  printf("v - copy\n");
  printMatrix(vc, size, 1);

  solveLinearSystem(m, v, size);

  printf("x\n");
  printMatrix(v, size, 1);
  prodMV(mc, v, size);
  printf("A*v\n");
  printMatrix(v, size, 1);
  double norm = diffNorm(v, vc, size);
  printf("norm = %lf\n", norm);
  if (isnan(norm)) {
    printf("error : norm = nan\n");
    exit(1);
  }
  if (norm - 0.0001 > 0) {
    printf("error : norm > 0.0001\n");
    exit(1);
  }
}
