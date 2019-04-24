#include <stdio.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *v, l;
  int size = 5;
  m = genMat(size, size);
  v = genVect(size);

  printf("a\n");
  printMatrix(m, size, size);
  printf("vect init\n");
  printVect(v, size);
  l = powerIt(m, v, size, 0.00000001, 10000);
  printf("l1 = %lf\n", l);
}
