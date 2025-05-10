#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

void divide(float** matrix, int row, int cols, float c) {
	for (int j = 0; j < cols; ++j) {
		matrix[row][j] = matrix[row][j] / c;
	}
}

void subtract(float** matrix, int row1, int row2, int cols, double c) {
	for (int j = 0; j < cols; ++j) {
		matrix[row1][j] = matrix[row1][j] - matrix[row2][j] * c;
	}
}

void printMatrix(float** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	std::cout << "------------------------" << std::endl;
}
void transform(float** matrix, int rows, int cols) { // Метод Гаусса - Жордана
	for (int i = 0; i < rows; ++i) {
		divide(matrix, i, cols, matrix[i][i]);
		for (int j = 0; j < rows; ++j) {
			if (i != j) {
				subtract(matrix, j, i, cols, matrix[j][i]);
			}
		}
	}

}
void solveSystem(float** matrix, int rows) {
	transform(matrix, rows, rows + 1);
	cout << "Решение системы:" << endl;
	for (int i = 0; i < rows; ++i) {
		cout << matrix[i][rows] << " ";
	}
	cout << endl;
}

int maxElem(float** matrix, int colnumber, int rows) {

	float max = 0;
	int temp = 0;
	for (int i = colnumber; i < rows; ++i) {

		if (abs(matrix[i][colnumber]) > max)
		{
			max = abs(matrix[i][colnumber]);
			temp = i;
		}
	}
	return temp;
}
void swapr(float** matrix, int row1, int row2, int cols) {

	float temp = 0;
	for (int i = 0; i < cols; ++i) {
		temp = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = temp;
	}
}
void transform2(float** matrix, int rows, int cols) { // Метод Гаусса - Жордана c выбором главного элемента по столбцу
	int temp = 0;
	for (int i = 0; i < rows; ++i) {
		temp = maxElem(matrix, i, rows);
		swapr(matrix, i, temp, cols);
		divide(matrix, i, cols, matrix[i][i]);
		for (int j = 0; j < rows; ++j) {
			if (i != j) {
				subtract(matrix, j, i, cols, matrix[j][i]);
			}
		}
	}
}
void solveSystem2(float** matrix, int rows) {
	transform2(matrix, rows, rows + 1);
	cout << "Решение системы:" << endl;
	for (int i = 0; i < rows; ++i) {
		cout << matrix[i][rows] << " ";
	}
	cout << endl;
}
int main() {
	int rows = 3, cols = 4;

	float** matrix = new float* [rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new float[cols];
	}
	setlocale(LC_ALL, "RU");
	cout << "Введите матрицу";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> matrix[i][j];
		}
	}

	cout << "Исходная матрица:" << endl;
	printMatrix(matrix, rows, cols);
	double t = omp_get_wtime();

	solveSystem(matrix, rows);
	cout << "Time: " << omp_get_wtime() - t << endl;

	return 0;
}