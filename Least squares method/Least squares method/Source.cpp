#include <iostream>
#include <cmath>

using namespace std;

void divide(float** matrix, int row, int cols, double c) {
	for (int j = 0; j < cols; ++j) {
		matrix[row][j] = matrix[row][j] / c;
	}
}

void subtract(float** matrix, int row1, int row2, int cols, double c) {
	for (int j = 0; j < cols; ++j) {
		matrix[row1][j] = matrix[row1][j] - matrix[row2][j] * c;
	}
}


void transform(float** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		divide(matrix, i, cols, matrix[i][i]);

#pragma omp parallel for schedule (static)
		for (int j = 0; j < rows; ++j) {
			if (i != j) {
				subtract(matrix, j, i, cols, matrix[j][i]);
			}
		}
	}
}

void solveSystem(float** matrix, int rows) {
	transform(matrix, rows, rows + 1);
}

void leastSquares(double x[], double y[], int n, double& k, double& b) {


	double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

	for (int i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2 += x[i] * x[i];
	}


	float** matrix = new float* [2];
	for (int i = 0; i < 2; ++i) {
		matrix[i] = new float[3];
	}
	matrix[0][0] = sum_x2;
	matrix[0][1] = sum_x;
	matrix[0][2] = sum_xy;

	matrix[1][0] = sum_x;
	matrix[1][1] = n;
	matrix[1][2] = sum_y;
	solveSystem(matrix, 2);
	k = matrix[0][2];
	b = matrix[1][2];
}
int main() {
	setlocale(LC_ALL, "ru");
	const int n = 6;
	double x[n] = { -1, 0, 1,2 ,3, 4 };
	double y[n] = { 0.86603, 1,0.86603, 0.5, 0, -0.5 };

	double k, b;
	leastSquares(x, y, n, k, b);

	cout << "Уравнение прямой: y = " << k << " * x + " << b << endl;


	return 0;
}