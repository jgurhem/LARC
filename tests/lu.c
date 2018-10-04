#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

int main(int argc, char **argv){

	double *m, *l, *u, *mc;
	int size = 5;
	m = genMat(size, size);
	mc = malloc(size * size * sizeof(double));

	memcpy(mc, m, size * size * sizeof(double));

	printf("a\n");
	printMatrix(m, size, size);
	printf("a\n");
	printMatrix(mc, size, size);

	factLU2(m, size);
	u = extractU(m, size, size);
	l = extractL(m, size, size);

	printf("a\n");
	printMatrix(m, size, size);
	printf("l\n");
	printMatrix(l, size, size);
	printf("u\n");
	printMatrix(u, size, size);


	prodMat(l, u, size);
	printf("rebuilt a\n");
	printMatrix(l, size, size);
	printf("norm = %lf\n", diffNorm(l, mc, size * size));
}
