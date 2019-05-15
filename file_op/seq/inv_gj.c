#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *m, *inv;
  int n = atoi(argv[1]);
  m = readBin(argv[2], n, n);
  inv = inversion(m, n);
  writeBin(argv[3], inv, n, n);
  free(m);
  free(inv);
}
