#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

double *read(char *Af, int nrow, int ncol, int nbf, char *ff, char *sep,
               int nb, int size) {
  double *A = 0;
  if (Af == 0)
    return 0;
  if (nbf == 1) {
    if (!strcmp(ff, "coo")) {
      A = readCOO(Af, nrow, ncol);
    } else if (!strcmp(ff, "binR")) {
      A = readBin(Af, nrow, ncol);
    }
  } else if (nbf == 2) {
    if (!strcmp(ff, "coo")) {
      if (ncol == 1) {
        A = readBlockVectorCOO(Af, nb, size);
      } else {
        A = readBlockMatrixCOO(Af, sep, nb, size);
      }
    } else if (!strcmp(ff, "binR")) {
      if (ncol == 1) {
        A = readBlockVectorBin(Af, nb, size);
      } else {
        A = readBlockMatrixBinR(Af, sep, nb, size);
      }
    }
  }
  return A;
}

void print_(int print, char *s, char *Af, double *A, int nrow, int ncol) {
  if (print && Af != 0) {
    printf("%s\n", s);
    printMatrix(A, nrow, ncol);
    printf("\n");
  }
}

void test_parameter_coherence(int nb, int size, int print, int nbf, int nbit,
                              double p, char *Af, char *Bf, char *Vf, char *Rf,
                              char *op, char *ff, char *sep) {
  if (nbf == 2 && sep == 0) {
    printf("No file coordinate separator provided.\n");
    exit(-1);
  }

  if (ff == 0) {
    printf("No file format provided.\n");
    exit(-1);
  }

  if (op == 0) {
    printf("No operation set.\n");
    exit(-1);
  }

  if (Af == 0) {
    if (!strcmp(op, "lu") || !strcmp(op, "blu") || !strcmp(op, "slsg") ||
        !strcmp(op, "invgj")) {
      printf("Operation %s needs A to be set\n", op);
      exit(-1);
    }
  }

  if (Bf == 0) {
    if (!strcmp(op, "lu") || !strcmp(op, "blu") || !strcmp(op, "invgj")) {
      printf("Operation %s needs B to be set\n", op);
      exit(-1);
    }
  }

  if (Vf == 0) {
    if (!strcmp(op, "slsg")) {
      printf("Operation %s needs V to be set\n", op);
      exit(-1);
    }
  }

  if (Rf == 0) {
    if (!strcmp(op, "slsg")) {
      printf("Operation %s needs R to be set\n", op);
      exit(-1);
    }
  }

  if (nb < 0 || size < 0) {
    printf("Negative size\n");
    exit(-1);
  }
}

void choice(int nb, int size, int print, int nbf, int nbit, double p, char *Af,
            char *Bf, char *Cf, char *Df, char *Vf, char *Rf, char *op,
            char *ff, char *sep) {

  test_parameter_coherence(nb, size, print, nbf, nbit, p, Af, Bf, Vf, Rf, op,
                           ff, sep);

  double *A = 0, *B = 0, *C = 0, *D = 0, *V = 0, *R = 0;
  int matsize = 0;
  if (nb >= 1)
    matsize = nb * size;
  else
    matsize = size;

  A = read(Af, matsize, matsize, nbf, ff, sep, nb, size);
  print_(print, "A", Af, A, matsize, matsize);
  B = read(Bf, matsize, matsize, nbf, ff, sep, nb, size);
  print_(print, "B", Bf, B, matsize, matsize);
  C = read(Cf, matsize, matsize, nbf, ff, sep, nb, size);
  print_(print, "C", Cf, C, matsize, matsize);
  D = read(Df, matsize, matsize, nbf, ff, sep, nb, size);
  print_(print, "D", Df, D, matsize, matsize);
  V = read(Vf, matsize, 1, nbf, ff, sep, nb, size);
  print_(print, "V", Vf, V, matsize, 1);
  R = read(Rf, matsize, 1, nbf, ff, sep, nb, size);
  print_(print, "R", Rf, R, matsize, 1);

  if (!strcmp(op, "blu")) {
    double *u, *l;
    l = extractMatrixL(nb, size, B);
    u = extractMatrixU(nb, size, B);
    print_(print, "l", Bf, l, matsize, matsize);
    print_(print, "u", Bf, u, matsize, matsize);
    prodMat(l, u, matsize);
    print_(print, "B - computed", Bf, l, matsize, matsize);
    printf("norm = %lf\n", diffNorm(l, A, matsize * matsize));
    free(l);
    free(u);
    return;
  }

  if (!strcmp(op, "slsg")) {
    gaussElimination(A, V, matsize);
    print_(print, "R - computed", Vf, V, matsize, 1);
    printf("norm = %lf\n", diffNorm(R, V, matsize));
    return;
  }

  if (!strcmp(op, "mm_d")) {
    prodDiff(A, B, C, matsize);
    print_(print, "D - computed", Cf, C, matsize, matsize);
    printf("norm = %lf\n", diffNorm(C, D, matsize * matsize));
    return;
  }

  if (!strcmp(op, "mm")) {
    prodMat(A, B, matsize);
    print_(print, "C - computed", Af, A, matsize, matsize);
    printf("norm = %lf\n", diffNorm(C, A, matsize * matsize));
    return;
  }

  if (!strcmp(op, "mv")) {
    prodMV(A, V, matsize);
    print_(print, "R - computed", Vf, V, matsize, 1);
    printf("norm = %lf\n", diffNorm(R, V, matsize));
    return;
  }

  if (!strcmp(op, "invgj")) {
    double *inv;
    inv = inversion(A, matsize);
    print_(print, "B - computed", Af, inv, matsize, matsize);
    printf("norm = %lf\n", diffNorm(inv, B, matsize * matsize));
    free(inv);
    return;
  }

  if (!strcmp(op, "dgeaxpxmv")) {
    double *res;
    res = dgeaxpxmv(A, V, matsize);
    print_(print, "R - computed", Vf, V, matsize, 1);
    printf("norm = %lf\n", diffNorm(res, R, matsize * matsize));
    free(res);
    return;
  }

  if (!strcmp(op, "powerIt")) {
    double l;
    l = powerIt(A, V, matsize, p, nbit);
    printf("l1 = %lf\n", l);
    return;
  }

  if (nbf == 1) {
    if (Af != 0) {
      free(A);
    }
    if (Bf != 0) {
      free(B);
    }
    if (Cf != 0) {
      free(C);
    }
    if (Df != 0) {
      free(D);
    }
    if (Vf != 0) {
      free(V);
    }
    if (Rf != 0) {
      free(R);
    }
  }
}

void help() {
  printf("--v show the version\n");
  printf("--help show this message\n");
  printf("[-A filepattern] initial matrix file\n");
  printf("[-B filepattern] result matrix file\n");
  printf("[-V filepattern] initial vector file\n");
  printf("[-R filepattern] result vector file\n");
  printf("[-b int] number of blocks\n");
  printf("[-s int] size of blocks\n");
  printf("[-p double] precision\n");
  printf("[-ff coo/binR] file format\n");
  printf("[-sep str] separator between coordinates of matrix files\n");
  printf("[-it int] maximum of iterations\n");
  printf("[-op operation] the operation may be lu, slslu, invbgj, slsb, "
         "slsbgj, powerIt, pmv, pdmv, mm_d (D=?C-A*B), mm (C=?A*B)...\n");
  printf("-one-file the matrices/vectors are stored in one file\n");
  printf("-multiple-file the matrices/vectors are stored in serveral files\n");
  printf("-print print the matrices and vectors\n");
}

int main(int argc, char **argv) {
  int nb = -1, size = -1, print = 0, nbf = 1, nbit = -1;
  double p = -1.0;
  char *Af = 0, *Bf = 0, *Cf = 0, *Df = 0, *Vf = 0, *Rf = 0, *op = 0, *ff = 0,
       *sep = 0;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--help")) {
      help();
      continue;
    }
    if (!strcmp(argv[i], "-print")) {
      print = 1;
      continue;
    }
    if (!strcmp(argv[i], "-one-file")) {
      nbf = 1;
      continue;
    }
    if (!strcmp(argv[i], "-multiple-file")) {
      nbf = 2;
      continue;
    }
    if (!strcmp(argv[i], "-it")) {
      if (++i >= argc)
        continue;
      nbit = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-p")) {
      if (++i >= argc)
        continue;
      p = atof(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-s")) {
      if (++i >= argc)
        continue;
      size = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-ff")) {
      if (++i >= argc)
        continue;
      ff = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-sep")) {
      if (++i >= argc)
        continue;
      sep = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-op")) {
      if (++i >= argc)
        continue;
      op = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-b")) {
      if (++i >= argc)
        continue;
      nb = atoi(argv[i]);
      continue;
    }
    if (!strcmp(argv[i], "-A")) {
      if (++i >= argc)
        continue;
      Af = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-B")) {
      if (++i >= argc)
        continue;
      Bf = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-C")) {
      if (++i >= argc)
        continue;
      Cf = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-D")) {
      if (++i >= argc)
        continue;
      Df = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-V")) {
      if (++i >= argc)
        continue;
      Vf = argv[i];
      continue;
    }
    if (!strcmp(argv[i], "-R")) {
      if (++i >= argc)
        continue;
      Rf = argv[i];
      continue;
    }
    help();
    break;
  }

  choice(nb, size, print, nbf, nbit, p, Af, Bf, Cf, Df, Vf, Rf, op, ff, sep);
  return 0;
}
