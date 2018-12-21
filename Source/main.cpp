#include <iostream>

using namespace std;

void generator_opt(double* &MatrixA, double* &MatrixB, double* &MatrixC, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MatrixA[i*N + j] = rand() % 100;
			MatrixB[i*N + j] = rand() % 100;
			MatrixC[i*N + j] = 0;
		}
	}
}
void generator_not_opt(double* MatrixA, double* MatrixB, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MatrixA[i*N + j] = rand() % 100;
			MatrixB[i*N + j] = rand() % 100;
		}
	}
}
void multiplication_optimize(double* &MatrixA, double* &MatrixB, double* &MatrixC1, int Size) {
	int BlockSize = 500;
	int GridSize = int(Size / double(BlockSize));
	for (int n = 0; n<GridSize; n++)
		for (int m = 0; m<GridSize; m++)
			for (int iter = 0; iter<GridSize; iter++)
				for (int i = n * BlockSize; i<(n + 1)*BlockSize; i++)
					for (int j = m * BlockSize; j<(m + 1)*BlockSize; j++)
						for (int k = iter * BlockSize; k<(iter + 1)*BlockSize; k++)
							MatrixC1[i*Size + j] += MatrixA[i*Size + k] * MatrixB[k*Size + j];
}

double* multiplication_not_optimize(double* MatrixA, double* MatrixB, int N) {
	double* MatrixC = new double[N*N];
	for (int i = 0; i<N; i++) {
		for (int j = 0; j<N; j++) {
			MatrixC[i*N + j] = 0;
			for (int k = 0; k<N; k++) {
				MatrixC[i*N + j] = MatrixC[i*N + j] + MatrixA[i*N + k] * MatrixB[k*N + j];
			}
		}
	}
	return MatrixC;
}

int main(int argc, char** argv) {
	int Size = 2000;
	int version = atoi(argv[1]);
	if (version == 0) {
		double* MatrixA = new double[Size*Size];
		double* MatrixB = new double[Size*Size];
	    double* MatrixC = new double[Size*Size];

		generator_opt(MatrixA, MatrixB, MatrixC, Size);
		multiplication_optimize(MatrixA, MatrixB, MatrixC, Size);
		delete[] MatrixA;
		delete[] MatrixB;
		delete[] MatrixC;
	}
	else if (version == 1) {
		double* MatrixA = (double*)malloc(Size*Size * sizeof(double));
		double* MatrixC = (double*)malloc(Size*Size * sizeof(double));
		double* MatrixB = (double*)malloc(Size*Size * sizeof(double)); 

		generator_not_opt(MatrixA, MatrixB, Size);
		MatrixC = multiplication_not_optimize(MatrixA, MatrixB, Size);
		free(MatrixA);
		free(MatrixB);
		free(MatrixC);
	}
}