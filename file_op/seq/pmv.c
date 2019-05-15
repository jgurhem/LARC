#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *m, *v;
  int n = atoi(argv[1]);
  m = readBin(argv[2], n, n);
  v = readBin(argv[3], n, 1);
  prodMV(m, v, n);
  writeBin(argv[3], v, n, 1);
  free(m);
  free(v);
}
