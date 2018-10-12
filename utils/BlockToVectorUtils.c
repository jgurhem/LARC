#include <string.h>
#include <stdlib.h>
#include <stdio.h>

double * genSingleVect(char * filePath, int bsize){
	FILE * f;
	f = fopen(filePath, "r");
	double * vect;

	vect = (double*) malloc(bsize*sizeof(double));

	int i,ii;
	double tmp;

	for(i = 0 ; i < bsize ; i++) {
		fscanf(f,"%d %lf",&ii,&tmp);
	  	vect[ii] = tmp;
	}
	fclose(f);

	return vect;
}

void genVectorBlockCOO(char * filePath, int nb, int bsize, double * vect, int ind){
	FILE * f;
	char matPath[150];
	char str[10];

	strcpy(matPath,filePath);
	sprintf(str, "%d", ind);
	strcat(matPath,str);
	//printf("%s \n",matPath);
	f = fopen(matPath, "r");

	int i,ii;
	double tmp;

	for(i = 0 ; i < bsize ; i++) {
	  	//fscanf(f,"%lf",&tmp);
	  	//vect[ind*bsize + i] = tmp;
		fscanf(f,"%d %lf",&ii,&tmp);
	  	vect[ind*bsize + ii] = tmp;
	  	//printf("%lf \n",tmp);
	}
	fclose(f);
}

void genVectorBlockBin(char * filePath, int nb, int bsize, double * vect, int ind){
	FILE * f;
	char matPath[150];
	char str[10];

	strcpy(matPath,filePath);
	sprintf(str, "%d", ind);
	strcat(matPath,str);
	f = fopen(matPath, "r");
	fread(vect + ind * bsize, sizeof(double), bsize, f);
	fclose(f);
}

double* importBlockVectorBin(char* filePath, int nb, int bsize){

	double * vect;
	int i;
	vect = (double*) malloc(nb*bsize*sizeof(double));
	for(i=0;i<nb;i++){
		genVectorBlockBin(filePath,nb, bsize, vect,i);
	}

	return vect;
}

double* importBlockVectorCOO(char* filePath, int nb, int bsize){

	double * vect;
	int i;
	vect = (double*) malloc(nb*bsize*sizeof(double));
	for(i=0;i<nb;i++){
		genVectorBlockCOO(filePath,nb, bsize, vect,i);
	}

	return vect;
}

void printVector(double *vect, int nb, int bsize){
	int i;
	for(i = 0 ; i < bsize * nb ; i++) { //row
		printf("%12lf\n",vect[ i] );
	}
}

void printVectorLatex(double *vect, int nb, int bsize){
	int i;
	for(i = 0 ; i < bsize * nb ; i++) { //row
		printf("%8.3lf",vect[ i] );
		if( i < bsize * nb - 1)
	  		printf("\\\\\n");
	}
	printf("\n");
}

void cleanVector(double *mat){
	free(mat);
}
