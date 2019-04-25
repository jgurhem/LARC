#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  int mycase = -1;
  if (argc == 1) {
    mycase = 1;
  } else if (argc == 2) {
    mycase = atoi(argv[1]);
  } else {
    printf("wrong number of argument.\n");
    exit(1);
  }

  if (mycase > 2 || mycase < 1) {
    printf("there is only 1...2 cases\n");
    exit(1);
  }

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

  switch (mycase) {
  case 1:
    printf("gaussElimination\n");
    gaussElimination(m, v, size);
    break;
  case 2:
    printf("gaussElimination2\n");
    gaussElimination2(m, v, size);
    break;
  }
  printf("x\n");
  printMatrix(v, size, 1);
  prodMV(mc, v, size);
  printf("A*x =? v\n");
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
