#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 5) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *a, *b, *c;
  int n = atoi(argv[1]);
  a = readBin(argv[2], n, n);
  b = readBin(argv[3], n, n);
  c = readBin(argv[4], n, n);
  prodDiff(a, b, c, n);
  writeBin(argv[4], c, n, n);
  free(a);
  free(b);
  free(c);
}
