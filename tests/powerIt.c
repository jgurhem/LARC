#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *v, l;
  int size = 4;
  // m = genMat(size, size);
  m = calloc(size * size, sizeof(double));
  v = genVect(size);

  m[0 * size + 0] = 2;
  m[1 * size + 1] = 2;
  m[2 * size + 2] = 3;
  m[3 * size + 3] = 3;
  m[3 * size + 2] = 1;
  m[2 * size + 1] = 1;
  m[1 * size + 0] = 1;

  printf("a\n");
  printMatrix(m, size, size);
  printf("vect init\n");
  printMatrix(v, size, 1);
  l = powerIt(m, v, size, 0.0000000001, 100000);
  printf("l1 = %lf\n", l);
  if (isnan(l)) {
    printf("error : l = nan\n");
    exit(1);
  }
  if (abs(l - 3) > 0.0001) {
    printf("error : abs(expected - real) > 0.0001\n");
    exit(1);
  }
}
