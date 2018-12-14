#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mvoputils.h>

void importBlockBinR(char* filePath, char* sep, double* m, int xls, int yls, int zls, int xgs, int ygs, int zgs, int xd, int yd, int zd, int xb, int yb, int zb){
	FILE * f;
	char path[150];
	sprintf(path, "%s%d%s%d%s%d", filePath, zb, sep, yb, sep, xb);
	//printf("x%d y%d z%d xls%d yls%d zls%d xd%d yd%d zd%d\n", xb, yb, zb, xls, yls, zls, xd, yd, zd);
	f = fopen(path, "r");
	if(f == NULL){
		printf("Cannot open file %s\n", path);
		exit(1);
	}
	int r = 0;
	for(int j = 0 ; j < zls; j++) {
		for(int i = 0 ; i < yls; i++) {
			r += fread(m + (zd + j) * ygs * xgs + (yd + i) * xgs + xd, sizeof(double), xls, f);
			if(r < xls){
				printf("cannot read %s entirely (%d / %d)\n", path, r, xls * yls * zls);
				exit(1);
			}
		}
	}
	fclose(f);
}

double* importMatrixBinR(char* filePath, char* sep, int Nx, int Ny, int Nz, int xgs, int ygs, int zgs, int* size){
	double *m;
	m = malloc(xgs * ygs * zgs * sizeof(double));
	for(int i = 0; i < Nz; i++){
		for(int j = 0; j < Ny; j++){
			for(int k = 0; k < Nx; k++){
				int xds = 0, yds = 0, zds = 0;
				for(int l = 0; l < k; l++){
					xds += size[3 * (i * Ny * Nx + j * Nx + l)];
				}
				for(int l = 0; l < j; l++){
					yds += size[3 * (i * Ny * Nx + l * Nx + k) + 1];
				}
				for(int l = 0; l < i; l++){
					zds += size[3 * (l * Ny * Nx + j * Nx + k) + 2];
				}
				importBlockBinR(filePath, sep, m, size[3 * (i * Ny * Nx + j * Nx + k)], size[3 * (i * Ny * Nx + j * Nx + k) + 1], size[3 * (i * Ny * Nx + j * Nx + k) + 2], xgs, ygs, zgs, xds, yds, zds, k, j, i);
			}
		}
	}
	return m;
}

int* computeParam(int Nx, int Ny, int Nz, int sx, int sy, int sz){
	int *size, x, y, z;
	size = malloc((Nx * Ny * Nz + 1) * 3 * sizeof(int));
	for(int i = 0; i < Nx * Ny * Nz; i++){
		x = (i % (Nx * Ny)) % Nx;
                y = (i % (Nx * Ny)) / Nx;
                z = i / Nx / Ny;

		size[3 * (z * Ny * Nx + y * Nx + x)] = sx / Nx;
		size[3 * (z * Ny * Nx + y * Nx + x) + 1] = sy / Ny;
		size[3 * (z * Ny * Nx + y * Nx + x) + 2] = sz / Nz;
		int mx = sx % Nx, my = sy % Ny, mz = sz % Nz;

		if(mx > x)
			size[3 * (z * Ny * Nx + y * Nx + x)] += 1;
		if(my > y)
			size[3 * (z * Ny * Nx + y * Nx + x) + 1] += 1;
		if(mz > z)
			size[3 * (z * Ny * Nx + y * Nx + x) + 2] += 1;
		//printf("r%03d x%d y%d z%d xDL%d yDL%d zDL%d\n", i, x, y, z, size[3 * (z * Ny * Nx + y * Nx + x)], size[3 * (z * Ny * Nx + y * Nx + x) + 1], size[3 * (z * Ny * Nx + y * Nx + x) + 2]);
	}

	size[3 * Nx * Ny * Nz] = 0;
	for(int i = 0; i < Nx; i++){
		size[3 * Nx * Ny * Nz] += size[3 * i];
	}
	return size;
}

void choice(int Nx, int Ny, int Nz, int sx, int sy, int sz, int print, char* Af, char* Bf, char* SFf, char* sep){

	double *A, *B, *SF;
	A = 0; B = 0; SF = 0;
	int *size;

	size = computeParam(Nx, Ny, Nz, sx, sy, sz);

	if(Af != 0){
		A = importMatrixBinR(Af, sep, Nx, Ny, Nz, sx, sy, sz, size);
	}
	if(Bf != 0){
		B = importMatrixBinR(Bf, sep, Nx, Ny, Nz, sx, sy, sz, size);
	}
	if(SFf != 0){
		SF = importBin(SFf, sz * sy, sx);
	}

	if(print){
		for(int i = 0; i < sz; i++){
			printf("z = %d\n", i);
			if(Af != 0){
				printf("A\n");
				printMatrixCompact(A + i * sy * sx, sy, sx);
				printf("\n");
			}
			if(Bf != 0){
				printf("B\n");
				printMatrixCompact(B + i * sy * sx, sy, sx);
				printf("\n");
			}
			if(SFf != 0){
				printf("SF\n");
				printMatrixCompact(SF + i * sy * sx, sy, sx);
				printf("\n");
			}
		}
	}

	if(Af != 0 && Bf != 0){
		printf("norm = %lf\n", diffNorm(B, A, sx * sy * sz));
	}

	if(SFf != 0 && Bf != 0){
		printf("norm = %lf\n", diffNorm(SF, B, sx * sy * sz));
	}

	if(SFf != 0 && Af != 0){
		printf("norm = %lf\n", diffNorm(SF, A, sx * sy * sz));
	}

	if(Af != 0){
		free(A);
	}
	if(Bf != 0){
		free(B);
	}
	if(SFf != 0){
		free(SF);
	}
}

void help(){
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
	printf("-print print the matrices and vectors\n");
}

int main(int argc, char ** argv){
	int sx = -1, sy = -1, sz = -1, Nx = -1, Ny = -1, Nz = -1, print = 0;
	char *Af = 0, *Bf = 0, *SFf = 0, *sep = 0;
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i],"--help")){
			help();
			continue;
		}
		if (!strcmp(argv[i],"-print")){
			print = 1;
			continue;
		}
		if (!strcmp(argv[i],"-sx")){
			if(++i >= argc)
				continue;
			sx = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-sy")){
			if(++i >= argc)
				continue;
			sy = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-sz")){
			if(++i >= argc)
				continue;
			sz = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-sep")){
			if(++i >= argc)
				continue;
			sep = argv[i];
			continue;
		}
		if (!strcmp(argv[i],"-Nx")){
			if(++i >= argc)
				continue;
			Nx = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-Ny")){
			if(++i >= argc)
				continue;
			Ny = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-Nz")){
			if(++i >= argc)
				continue;
			Nz = atoi(argv[i]);
			continue;
		}
		if (!strcmp(argv[i],"-A")){
			if(++i >= argc)
				continue;
			Af = argv[i];
			continue;
		}
		if (!strcmp(argv[i],"-SF")){
			if(++i >= argc)
				continue;
			SFf = argv[i];
			continue;
		}
		if (!strcmp(argv[i],"-B")){
			if(++i >= argc)
				continue;
			Bf = argv[i];
			continue;
		}
		help();
		break;
	}

	choice(Nx, Ny, Nz, sx,sy, sz, print, Af, Bf, SFf, sep);
	return 0;
}
