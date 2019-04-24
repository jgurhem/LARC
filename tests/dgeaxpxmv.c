#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {

  double *m, *v, *y;
  int size = 5;
  v = malloc(size * sizeof(double));
  // m = genMat(size, size);
  m = calloc(size * size, sizeof(double));
  ;

  for (int i = 0; i < size; i++) {
    for (int k = 0; k < size; k++) {
      m[i + size * k] = i + size * k;
    }
    v[i] = i + 1;
  }

  printf("a\n");
  printMatrix(m, size, size);
  printf("\n\nv\n");
  printVect(v, size);

  y = dgeaxpxmv(m, v, size);

  printf("\n\nv\n");
  printVect(y, size);
}
