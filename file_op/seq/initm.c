#include <stdio.h>
#include <stdlib.h>

#include <mvoputils.h>

int main(int argc, char **argv) {
  if (argc != 5) {
    printf("Wrong number of parameters!\n");
    exit(1);
  }
  double *m;
  int nbr = atoi(argv[1]);
  int nbc = atoi(argv[2]);
  int seed = atoi(argv[3]);
  srand(seed);
  m = genMat(nbr, nbc);
  writeBin(argv[4], m, nbr, nbc);
  free(m);
}
