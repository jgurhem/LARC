#include <stdlib.h>
#include <stdio.h>

double * genVect(int nbRow){

	double * mat;
	int i;

	mat = (double*) malloc(nbRow*sizeof(double));

	for(i=0; i<nbRow; i++)
		mat[i] = 100.0 * rand() / RAND_MAX;

	return mat;
}

void printVect(double *mat, int nbRow){
	int i;
	for(i=0;i<nbRow;i++){
		printf("%lf\n",mat[i]);
	}
}
