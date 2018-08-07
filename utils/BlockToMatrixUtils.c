#include <string.h>
#include <stdlib.h>
#include <stdio.h>

double * genSingleMat(char * filePath, int bsize){
	FILE * f;
	f = fopen(filePath, "r");
	double * mat;

	mat = (double*) malloc(bsize*bsize*sizeof(double));

	int i,j,nbRow,nbCol,indI,indJ;
	double tmp;

	for(i = 0 ; i < bsize ; i++) { //row
	  for(j = 0; j < bsize ; j++) { //col
	  	fscanf(f,"%d %d %lf",&indI,&indJ,&tmp);
		mat[indI*bsize + indJ] = tmp;
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

	int i,j,nbRow,nbCol,indI,indJ;
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

	int i,j,nbRow,nbCol;
	double tmp;

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

	int i,j,nbRow,nbCol;
	double tmp;

	for(i = 0 ; i < bsize ; i++) { //row
	  for(j = 0; j < bsize ; j++) { //col
			mat[(blockRow*bsize + i)*nb*bsize + blockCol*bsize + j] = 0;
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

void printMatrix(double *mat, int nb, int bsize){
	int i,j;
	for(i = 0 ; i < bsize * nb ; i++) { //row
	  for(j = 0; j < bsize * nb; j++) { //col
		printf("%14lf",mat[ i*nb*bsize + j] );
	  }
	  printf("\n");
	}
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

double * extractL(double *in, int nbRow, int nbCol){

        double * mat;
        int i,j;

        mat = (double*) malloc(nbCol*nbRow*sizeof(double));

        for(i=0; i<nbRow; i++)
                for(j=0; j<nbCol; j++)
                        if(i>j)
                                mat[i*nbCol+j] = in[i*nbCol+j];
                        else if(i==j)
                                mat[i*nbCol+j] = 1;
                        else
                                mat[i*nbCol+j] = 0;

        return mat;
}

double * extractU(double *in, int nbRow, int nbCol){

        double * mat;
        int i,j;

        mat = (double*) malloc(nbCol*nbRow*sizeof(double));

        for(i=0; i<nbRow; i++)
                for(j=0; j<nbCol; j++)
                        if(i<=j)
                                mat[i*nbCol+j] = in[i*nbCol+j];
                        else
                                mat[i*nbCol+j] = 0;

        return mat;
}
