#include <string.h>
#include <stdlib.h>
#include <stdio.h>

double * genSingleMat(char * filePath, int nbRow, int nbCol){
	FILE * f;
	f = fopen(filePath, "r");
	double * mat;

	mat = (double*) malloc(nbCol * nbRow * sizeof(double));

	int i, j, indI, indJ;
	double tmp;

	for(i = 0; i < nbRow; i++) { //row
		for(j = 0; j < nbCol; j++) { //col
			fscanf(f, "%d %d %lf", &indI, &indJ, &tmp);
			mat[indI * nbCol + indJ] = tmp;
			//printf("i-%d j-%d indi-%d indj-%d %lf \n",i,j,indI,indJ,tmp);
		}
		//printf("\n");
	}
	fclose(f);

	return mat;
}

void genMatrixBlock(char * filePath, int nb, int bsize, double * mat, int blockRow, int blockCol){
	FILE * f;
	char matPath[150];
	char str[10];

	strcpy(matPath,filePath);

	sprintf(str, "%d", blockRow);
	strcat(matPath,str);

	strcat(matPath,",");

	sprintf(str, "%d", blockCol);
	strcat(matPath,str);
	//printf("%s \n",matPath);
	f = fopen(matPath, "r");

	int i,j,indI,indJ;
	double tmp;

	for(i = 0 ; i < bsize ; i++) { //row
		for(j = 0; j < bsize ; j++) { //col
			//fscanf(f,"%lf",&tmp);
			fscanf(f,"%d %d %lf",&indI,&indJ,&tmp);
			//mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = tmp;
			mat[(blockRow*bsize + indI)*nb*bsize + blockCol*bsize + indJ] = tmp;
			//printf("i-%d j-%d indi-%d indj-%d %lf \n",i,j,indI,indJ,tmp);
		}
		//printf("\n");
	}
	fclose(f);
}

void genBlockUnit(int nb, int bsize, double * mat, int blockRow, int blockCol){

	int i,j;

	for(i = 0 ; i < bsize ; i++) { //row
		for(j = 0; j < bsize ; j++) { //col
			if(j==i)
				mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = 1;
			else
				mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = 0;
		}
	}
}

void genBlockZero(int nb, int bsize, double * mat, int blockRow, int blockCol){

	int i,j;

	for(i = 0 ; i < bsize ; i++) { //row
		for(j = 0; j < bsize ; j++) { //col
			mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = 0;
		}
	}
}

void extractBlock(int nb, int bsize, double * src, double * dst, int blockRow, int blockCol){

	int i,j;

	for(i = 0 ; i < bsize ; i++) { //row
		for(j = 0; j < bsize ; j++) { //col
			dst[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = src[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j];
		}
	}
}

double * genMatrixA(char* filePath, int nb, int bsize){

	double * mat;
	int i,j;
	mat = (double*) malloc(nb*nb*bsize*bsize*sizeof(double));
	for(i=0;i<nb;i++){
		for(j=0;j<nb;j++){
			genMatrixBlock(filePath,nb, bsize, mat,i ,j);
		}
	}

	return mat;
}

double * extractMatrixU(int nb, int bsize, double *src){
    double *mat;
    int i, j;
    mat = (double*) malloc(nb * nb * bsize * bsize * sizeof(double));
    for(i = 0; i < nb; i++){
        for(j = 0; j < nb; j++){
            if(i <= j)
                extractBlock(nb, bsize, src, mat, i, j);
            else
                genBlockZero(nb, bsize, mat, i, j);
        }
    }
    return mat;
}

double * genMatrixU(char* filePath, int nb, int bsize){

	double * mat;
	int i,j;
	mat = (double*) malloc(nb*nb*bsize*bsize*sizeof(double));
	for(i=0;i<nb;i++){
		for(j=0;j<nb;j++){
			if(i<=j)
				genMatrixBlock(filePath,nb, bsize, mat,i ,j);
			else
				genBlockZero(nb, bsize, mat,i ,j);
		}
	}

	return mat;
}

double * extractMatrixL(int nb, int bsize, double *src){
    double *mat;
    int i, j;
    mat = (double*) malloc(nb * nb * bsize * bsize * sizeof(double));
    for(i = 0; i < nb; i++){
        for(j = 0; j < nb; j++){
            if(i > j)
                extractBlock(nb, bsize, src, mat, i, j);
            else if(i==j)
                genBlockUnit(nb, bsize, mat,i ,j);
            else
                genBlockZero(nb, bsize, mat, i, j);
        }
    }
    return mat;
}

double * genMatrixL(char* filePath, int nb, int bsize){

	double * mat;
	int i,j;
	mat = (double*) malloc(nb*nb*bsize*bsize*sizeof(double));
	for(i=0;i<nb;i++){
		for(j=0;j<nb;j++){
			if(i>j)
				genMatrixBlock(filePath,nb, bsize, mat,i ,j);
			else if(i==j)
				genBlockUnit(nb, bsize, mat,i ,j);
			else
				genBlockZero(nb, bsize, mat,i ,j);
		}
	}
	return mat;
}

void printMatrixLatex(double *mat, int nb, int bsize){
	int i,j;
	for(i = 0 ; i < bsize * nb ; i++) { //row
		for(j = 0; j < bsize * nb; j++) { //col
			printf("%8.3lf",mat[ i*nb*bsize + j] );
			if( j < bsize * nb - 1)
				printf(" &");
		}
		printf("\\\\\n");
	}
}

void cleanMatrix(double *mat){
	free(mat);
}
