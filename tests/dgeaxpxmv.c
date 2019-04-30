#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *v, *y, *r;
  int size = 5;
  v = calloc(size, sizeof(double));
  r = calloc(size, sizeof(double));
  // m = genMat(size, size);
  m = calloc(size * size, sizeof(double));

  for (int i = 0; i < size; i++) {
    m[i + size * i] = 1;
    v[i] = i + 1;
    r[i] = 3 * (i + 1);
  }

  printf("a\n");
  printMatrix(m, size, size);
  printf("v\n");
  printMatrix(v, size, 1);

  y = dgeaxpxmv(m, v, size);

  printf("r\n");
  printMatrix(y, size, 1);
  printf("r - computed\n");
  printMatrix(r, size, 1);

  double norm = diffNorm(y, r, size);
  printf("norm = %lf\n", norm);
  if (isnan(norm)) {
    printf("error : norm = nan\n");
    exit(1);
  }
  if (norm - 0.0001 > 0) {
    printf("error : norm > 0.0001\n");
    exit(1);
  }
  free(y);
  free(v);
  free(r);
  free(m);
}
