#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *v;
  int size = atoi(argv[1]);
  int seed = atoi(argv[2]);
  srand(seed);
  v = genVect(size);
  writeBin(argv[3], v, size, 1);
  free(v);
}
