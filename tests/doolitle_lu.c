#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *l, *u, *mc;
  int size = 7;
  m = genMat(size, size);
  mc = malloc(size * size * sizeof(double));

  memcpy(mc, m, size * size * sizeof(double));

  printf("a\n");
  printMatrix(m, size, size);

  doolittleLU(m, size);
  u = extractU(m, size, size);
  l = extractL(m, size, size);

  printf("a\n");
  printMatrix(m, size, size);
  printf("l\n");
  printMatrix(l, size, size);
  printf("u\n");
  printMatrix(u, size, size);

  prodMat(l, u, size);
  printf("l*u\n");
  printMatrix(l, size, size);
  double norm = diffNorm(l, mc, size * size);
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
