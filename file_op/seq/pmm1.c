#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *m1, *m2;
  int n = atoi(argv[1]);
  m1 = readBin(argv[2], n, n);
  m2 = readBin(argv[3], n, n);
  prodMat(m1, m2, n);
  writeBin(argv[2], m1, n, n);
  free(m1);
  free(m2);
}
