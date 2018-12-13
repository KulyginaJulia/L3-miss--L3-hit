#include <iostream>

using namespace std;

void generator(double* &MatrixA, double* &MatrixB, double* &MatrixC1, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MatrixA[i*N + j] = rand() % 100;
			MatrixB[i*N + j] = rand() % 100;
			MatrixC1[i*N + j] = 0;
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

void multiplication_not_optimize(double* &MatrixA, double* &MatrixB, double* &MatrixC, int N) {
	for (int i = 0; i<N; i++) {
		for (int j = 0; j<N; j++) {
			MatrixC[i*N + j] = 0;
			for (int k = 0; k<N; k++) {
				MatrixC[i*N + j] = MatrixC[i*N + j] + MatrixA[i*N + k] * MatrixB[k*N + j];
			}
		}
	}
}

void multiplication_column(double* &MatrixA, double* &MatrixB, double* &MatrixC2, int N) {
	int i, j;
	for (int i = 0; i < N*N; i++) {
		MatrixC2[i] = 0;
	}
	for (i = 0; i<N; i++) { 
		for (int k = 0; k < N; k++) {
			for (j = 0; j < N; j++)
				MatrixC2[j*N + k] += MatrixA[j*N + i] * MatrixB[i*N + k];
		}
	}

}

int main(int argc, char** argv) {
#if 1
	int Size = 2000;
	double* MatrixA = new double[Size*Size];
	double* MatrixB = new double[Size*Size];
	double* MatrixC = new double[Size*Size];

	generator(MatrixA, MatrixB, MatrixC, Size);
#endif
	int version = atoi(argv[1]);
	if (version == 0) {
		multiplication_optimize(MatrixA, MatrixB, MatrixC, Size);
	}
	else if (version == 1) {
		//multiplication_not_optimize(MatrixA, MatrixB, MatrixC1, Size);
		multiplication_column(MatrixA, MatrixB, MatrixC, Size);
	}
}