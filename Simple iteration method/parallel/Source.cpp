#include <iostream>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;

float norm(float v[], int n) {
	float norma = 0.0;
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		norma = max(norma, abs(v[i]));
	}
	return norma;
}

void vectorSum(float v1[], float v2[], float result[], int n) {
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		result[i] = v1[i] + v2[i];
	}
}

float mnorm(float** arr, int n) {
	float maxRowSum = 0;
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		float rowSum = 0;
		for (int j = 0; j < n; ++j) {
			rowSum += abs(arr[i][j]);
		}
		maxRowSum = max(maxRowSum, rowSum);
	}
	return maxRowSum;
}

void vectorMult(float v[], float num, float result[], int n) {
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		result[i] = v[i] * num;
	}
}

void matrixVectorMult(float** arr, float v[], float result[], int n) {
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		result[i] = 0.0;
		for (int j = 0; j < n; ++j) {
			result[i] += arr[i][j] * v[j];
		}
	}
}

void transformToH(float** arr, int n) {
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		float divisor = arr[i][i];

		for (int j = 0; j < n; ++j) {
			if (i == j) {
				arr[i][j] = 0.0;
			}
			else {
				arr[i][j] = -arr[i][j] / divisor;
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			std::cout << arr[i][j] << " ";
		std::cout << endl;
	}

}


void next(float** arr, float b[], float x[], float x_next[], int n) {
	matrixVectorMult(arr, x, x_next, n);
	vectorSum(x_next, b, x_next, n);

}

void simpleIter(float** arr, float b[], float x[], float epsilon, int n, float result[]) {
	float criterion = 0;
#pragma omp parallel for
	for (int i = 0; i < n; ++i)
		b[i] = b[i] / arr[i][i];
	float* x_prev = new float[n];
	float* x_next = new float[n];
	for (int i = 0; i < n; ++i)
	{
		x_next[i] = 0;
	}
	transformToH(arr, n);
	do {
		for (int i = 0; i < n; ++i)
		{
			x_prev[i] = x_next[i];
		}
		next(arr, b, x_prev, x_next, n);
		float H_norm = mnorm(arr, n);
		float* diff = new float[n];
		for (int i = 0; i < n; ++i) {
			diff[i] = x_next[i] - x_prev[i];
		}
		criterion = (H_norm / (1 - H_norm)) * norm(diff, n);
		delete[] diff;


	} while (abs(criterion) >= epsilon);
	for (int i = 0; i < n; ++i)
	{
		result[i] = x_prev[i];
	}
}

int main() {
	const int n = 3;
	float epsilon = 1e-6;
	float** matrix = new float* [n];
	for (int i = 0; i < n; ++i) {
		matrix[i] = new float[n];
	}
	float b[n];
	for (int i = 0; i < n; ++i) {++++
		b[i] = 0;
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cin >> matrix[i][j];
		cin >> b[i];
	}
	cout << "-------------------------------------------" << endl;
	float start[n];
	float result[n];
	for (int i = 0; i < n; ++i) {
		start[i] = 0;
	}
	simpleIter(matrix, b, start, epsilon, n, result);
	cout << "--------------------------------------------" << endl;;
	for (int i = 0; i < n; ++i)
		cout << result[i];
	return 0;
}