#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//C=C-A*B
void prodDiff(double*A, double*B, double*C,int size){
	int i,j,k;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			for(k=0;k<size;k++){
				C[i*size+j] = C[i*size+j] - A[i*size+k]*B[k*size+j];
			}
		}
	}
}

//y=y-A*x
void prodDiffMV(double*A, double*x, double*y,int size){
	int i,k;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			y[i] = y[i] - A[i*size+k]*x[k];
		}
	}
}

//x=A*x
void prodMV(double*A, double*x, int size){
	int i,k;

	double * tmp;
	tmp = (double*) malloc(size*sizeof(double));

	for(i=0;i<size;i++){
		tmp[i] = 0;
		for(k=0;k<size;k++){
			tmp[i] += A[i*size+k]*x[k];
		}
	}

	memcpy(x,tmp,size*sizeof(double));
	free(tmp);
}

//A=A*B
void prodMat(double*A, double*B, int size){
	int i,j,k;

	double * tmp;
	tmp = (double*) malloc(size*size*sizeof(double));

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tmp[i*size+j] = 0;
			for(k=0;k<size;k++){
				tmp[i*size+j] = tmp[i*size+j] + A[i*size+k]*B[k*size+j];
			}
		}
	}

	memcpy(A,tmp,size*size*sizeof(double));
	free(tmp);
}

//return C=A*B
double* mProdMat(double*A, double*B, int size){
	int i,j,k;

	double * tmp;
	tmp = (double*) malloc(size*size*sizeof(double));

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tmp[i*size+j] = 0;
			for(k=0;k<size;k++){
				tmp[i*size+j] -= A[i*size+k]*B[k*size+j];
			}
		}
	}
	return tmp;
}

//B=A*B
void prodMat2(double*A, double*B, int size){
	int i,j,k;

	double * tmp;
	tmp = (double*) malloc(size*size*sizeof(double));

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			for(k=0;k<size;k++){
				tmp[i*size+j] = tmp[i*size+j] + A[i*size+k]*B[k*size+j];
			}
		}
	}

	memcpy(B,tmp,size*size*sizeof(double));
	free(tmp);
}

//B=A^-1
double * inversion(double*A, int size){
	int i,j,k;
	double temp;
	double *B;

	B = malloc(size*size*sizeof(double));

	for (i=0 ; i< size; i++){
		for (j=0 ; j< size; j++){
			if(j==i)
				B[i*size+i] = 1.000;
			else
				B[i*size+j] = 0.000;
		}
	}

	for (k=0 ; k < size ; k++ ){
		temp = A[k*size+k];
		for (j=0 ; j< size ; j++){
			i=k;
			A[i*size+j] =  A[i*size+j]/temp;
			B[i*size+j] = B[i*size+j]/temp;
		}

		for (i=0 ; i< size ; i++){
			if (i!=k){
				temp = A[i*size+k];
				for (j=0 ; j< size ; j++){
					A[i*size+j] = A[i*size+j] - temp*A[k*size+j];
					B[i*size+j] = B[i*size+j] - temp*B[k*size+j];
				}
			}
		}

	}
	return B;
}

void factLU(double* A, int size){

	int i,j,k;

	for(j=0;j<size;j++){
		for(i=0;i<size;i++){
			if (i<j){
				for (k=i+1; k<size; k++ )
					A[k*size+j] = A[k*size+j] - A[k*size+i] * A[i*size+j];
			} else if(i!=j)
				A[i*size+j] = A[i*size+j] / A[j*size+j];
		}
	}

}

void factLU2(double* A, int size){

	int i,j,k;

	for (k=0; k<size-1; k++ ){
		for(i=k+1;i<size;i++){
			A[i*size+k] = A[i*size+k] / A[k*size+k];
			for(j=k+1;j<size;j++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}
		}
	}
}

void resLx(double *A, double *b, int size){
	int i,k;

	for(i=0;i<size-1;i++){
		for (k=i+1;k<size;k++){
			b[k] = b[k] - A[k*size+i] * b[i];
		}
	}
}

void resUx(double *A, double *b, int size){
	int i,k;

	for(i=size-1;i>=0;i--){
		b[i] = b[i] / A[i*size+i];
		for (k=0;k<i;k++){
			b[k] = b[k] - A[k*size+i] * b[i];
		}
	}
}

void solveLinearSystem(double *A, double *b, int size){
	factLU2(A,size);
	resLx(A,b,size);
	resUx(A,b,size);
}

void gaussElimination(double *A, double *B, int size){
	int i,j,k;

	for(k=0;k<size-1;k++){
		for(i=k+1;i<size;i++){
			A[k*size+i] = A[k*size+i] / A[k*size+k];
		}
		B[k] = B[k] / A[k*size+k];


		/*
		   for(i=k+1;i<size;i++){
		   for(j=k+1;j<size;j++){
		   A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
		   }
		   B[i] = B[i] - A[i*size+k] * B[k];
		   }
		 */

		for(j=k+1;j<size;j++){
			for(i=k+1;i<size;i++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}
			B[j] = B[j] - A[j*size+k] * B[k];
		}
	}

	B[size-1] = B[size-1] / A[size*size-1];

	for(k=size-1;k>0;k--){
		for (i=0;i<k;i++){
			B[i] = B[i] - A[i*size+k] * B[k];
		}
	}
}

void gaussElimination2(double *A, double *B, int size){
	int i,j,k;

	for(k=0;k<size;k++){

		B[k] = B[k] / A[k*size+k];

		if(k != size-1){ //inutile en C puisque le for gére ce cas tout seul mais pas YML
			for(i=k+1;i<size;i++){
				A[k*size+i] = A[k*size+i] / A[k*size+k];
			}

			for(j=k+1;j<size;j++){
				for(i=k+1;i<size;i++){
					A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
				}
				B[j] = B[j] - A[j*size+k] * B[k];
			}
		}
	}

	for(k=size-1;k>0;k--){
		for (i=0;i<k;i++){
			B[i] = B[i] - A[i*size+k] * B[k];
		}
	}
}

void gaussElimination3(double *A, double *B, int size){
	int i,j,k;
	for(k=0;k<size-1;k++){

		for(i=k+1;i<size;i++){
			A[i*size+k] = A[i*size+k] / A[k*size+k];
			B[i] = B[i] - A[i*size+k] * B[k];
		}


		for(i=k+1;i<size;i++){
			for(j=k+1;j<size;j++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}
		}
	}


	for(k=size-1;k>=0;k--){
		B[k] = B[k] / A[k*size+k];
		for (i=0;i<k;i++){
			B[i] = B[i] - A[i*size+k] * B[k];
		}
	}
}

void gaussElimination4(double *A, double *B, int size){
	int i,j,k;
	for(k=0;k<size;k++){

		B[k] = B[k] / A[k*size+k];

		for(i=k+1;i<size;i++){
			A[k*size+i] = A[k*size+i] / A[k*size+k];
			B[i] = B[i] - A[i*size+k] * B[k];
		}

		for(i=k+1;i<size;i++){
			for(j=k+1;j<size;j++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}
		}
	}

	for(k=size-1;k>0;k--){
		for (i=0;i<k;i++){
			B[i] = B[i] - A[i*size+k] * B[k];
		}
	}
}


void gaussJordan(double *A, double *B, int size){
	int i,j,k;

	for(k=0;k<size;k++){
		for(i=k+1;i<size;i++){
			A[k*size+i] = A[k*size+i] / A[k*size+k];
		}
		B[k] = B[k] / A[k*size+k];

		for(j=k+1;j<size;j++){
			for(i=k+1;i<size;i++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}

			for(i=0;i<k;i++){
				A[i*size+j] = A[i*size+j] - A[i*size+k] * A[k*size+j];
			}
		}

		for(j=0;j<size;j++)
			if(j!=k){
				B[j] = B[j] - A[j*size+k] * B[k];
				//printf("Im here k %d j %d\n", k, j);
			}

	}
}

double diffNorm(double *A, double *B, int size){
	double diff=0;
	int i;
	for(i=0; i<size; i++){
		diff += fabs(A[i]-B[i])*fabs(A[i]-B[i]);
	}

	return sqrt(diff);
}
