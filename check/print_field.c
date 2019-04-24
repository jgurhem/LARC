#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

void importBlockBinR(char *filePath, char *sep, double *mat, int bsRow,
                     int bsCol, int gsCol, int startR, int startC, int blockRow,
                     int blockCol) {
  FILE *f;
  char matPath[150];
  sprintf(matPath, "%s%d%s%d", filePath, blockRow, sep, blockCol);
  // printf("c%d l%d lr%d lc%d gc%d sr%d sc%d\n", blockCol, blockRow, bsRow,
  // bsCol, gsCol, startR, startC);
  f = fopen(matPath, "r");
  if (f == NULL) {
    printf("Cannot open file %s\n", matPath);
    exit(1);
  }
  int r = 0;
  for (int i = 0; i < bsRow; i++) { // row
    r += fread(mat + (startR + i) * gsCol + startC, sizeof(double), bsCol, f);
    if (r < bsCol) {
      printf("cannot read %s entirely (%d / %d)\n", matPath, r, bsRow * bsCol);
      exit(1);
    }
  }
  fclose(f);
}

double *importMatrixBinR(char *filePath, char *sep, int nbRow, int nbCol,
                         int gsRow, int gsCol, int *size) {
  double *m;
  m = malloc(gsRow * gsCol * sizeof(double));
  for (int i = 0; i < nbCol; i++) {
    for (int j = 0; j < nbRow; j++) {
      int startR = 0, startC = 0;
      for (int k = 0; k < i; k++) {
        startC += size[2 * k];
      }
      for (int k = 0; k < j; k++) {
        startR += size[2 * k * nbCol + 1];
      }
      importBlockBinR(filePath, sep, m, size[2 * (j * nbCol + i) + 1],
                      size[2 * (j * nbCol + i)], gsCol, startR, startC, j, i);
    }
  }
  return m;
}

int *computeParam(int bx, int sx, int sy, int nbProc, int nbLocIt) {
  int *size;
  size = malloc((nbProc + 1) * 2 * sizeof(int));
  int by = nbProc / bx, x, y;
  if (by * bx != nbProc) {
    printf("Total number of processes different from dim1 x dim2\n");
    exit(1);
  }
  for (int i = 0; i < nbProc; i++) {
    x = i % bx;
    y = i / bx;

    size[2 * i] = sx / bx;
    size[2 * i + 1] = sy / by;
    int mx = sx % bx, my = sy % by;

    if (mx > x)
      size[2 * i] += 1;
    if (my > y)
      size[2 * i + 1] += 1;

    if (x != 0)
      size[2 * i] += nbLocIt;
    if (y != 0)
      size[2 * i + 1] += nbLocIt;

    if (x != bx - 1)
      size[2 * i] += nbLocIt;
    if (y != by - 1)
      size[2 * i + 1] += nbLocIt;

    // printf("r%d c%d l%d xDL%d yDL%d\n", i, x, y, size[2 * i], size[2 * i +
    // 1]);
  }

  size[2 * nbProc] = 0;
  for (int i = 0; i < bx; i++) {
    size[2 * nbProc] += size[2 * i];
  }
  size[2 * nbProc + 1] = 0;
  for (int i = 0; i < by; i++) {
    size[2 * nbProc + 1] += size[2 * i * bx + 1];
  }

  return size;
}

void choice(int bx, int sx, int sy, int nbProc, int nbLocIt, int print,
            char *Af, char *Bf, char *SFf, char *sep) {

  double *A, *B, *SF;
  A = 0;
  B = 0;
  SF = 0;
  int *size;

  size = computeParam(bx, sx, sy, nbProc, nbLocIt);

  if (Af != 0) {
    A = importMatrixBinR(Af, sep, nbProc / bx, bx, size[2 * nbProc + 1],
                         size[2 * nbProc], size);
  }
  if (Bf != 0) {
    B = importMatrixBinR(Bf, sep, nbProc / bx, bx, size[2 * nbProc + 1],
                         size[2 * nbProc], size);
  }
  if (SFf != 0) {
    SF = importBin(SFf, sy, sx);
  }

  if (print) {
    if (Af != 0) {
      printf("A\n");
      printMatrixCompact(A, size[2 * nbProc + 1], size[2 * nbProc]);
      printf("\n");
    }
    if (Bf != 0) {
      printf("B\n");
      printMatrixCompact(B, size[2 * nbProc + 1], size[2 * nbProc]);
      printf("\n");
    }
    if (SFf != 0) {
      printf("SF\n");
      printMatrixCompact(SF, sy, sx);
      printf("\n");
    }
  }

  if (Af != 0 && Bf != 0) {
    printf("norm = %lf\n",
           diffNorm(B, A, size[2 * nbProc] * size[2 * nbProc + 1]));
  }

  if (SFf != 0 && Bf != 0 && nbLocIt == 0) {
    printf("norm = %lf\n", diffNorm(SF, B, sx * sy));
  }

  if (Af != 0) {
    free(A);
  }
  if (Bf != 0) {
    free(B);
  }
}

void help() {
  printf("--v show the version\n");
  printf("--help show this message\n");
  printf("[-A filepattern] initial matrix file\n");
  printf("[-B filepattern] result matrix file\n");
  printf("[-b int] number of blocks\n");
  printf("[-s int] size of blocks\n");
  printf("[-p double] precision\n");
  printf("[-ff coo/binR] file format\n");
  printf("[-sep str] separator between coordinates of matrix files\n");
  printf("[-it int] maximum of iterations\n");
  printf("[-op operation] the operation may be lu, slslu, invbgj, slsb, "
         "slsbgj, powerIt, pmv, pdmv...\n");
  printf("-print print the matrices and vectors\n");
}

int main(int argc, char **argv) {
  int nbLocIt = -1, bx = -1, sx = -1, sy = -1, nbProc = -1, print = 0;
  char *Af = 0, *Bf = 0, *SFf = 0, *sep = 0;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--help")) {
      help();
      continue;
    }
    if (!strcmp(argv[i], "-print")) {
      print = 1;
      continue;
    }
    if (!strcmp(argv[i], "-sx")) {
      if (++i >= argc)
        continue;
      sx = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-sy")) {
      if (++i >= argc)
        continue;
      sy = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-n")) {
      if (++i >= argc)
        continue;
      nbProc = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-sep")) {
      if (++i >= argc)
        continue;
      sep = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-bx")) {
      if (++i >= argc)
        continue;
      bx = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-nbLocIt")) {
      if (++i >= argc)
        continue;
      nbLocIt = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-A")) {
      if (++i >= argc)
        continue;
      Af = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-SF")) {
      if (++i >= argc)
        continue;
      SFf = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-B")) {
      if (++i >= argc)
        continue;
      Bf = argv[i];
      continue;
    }
    help();
    break;
  }

  choice(bx, sx, sy, nbProc, nbLocIt, print, Af, Bf, SFf, sep);
  return 0;
}
