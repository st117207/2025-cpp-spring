#include <iostream>
#include <cmath>
#include <cstdlib>
#include <omp.h>

using namespace std;

double function(double x, double alpha, double beta) {
	return 1.0 / (sqrt(1 - 2 * alpha * x + alpha * alpha) * sqrt(1 - 2 * beta * x + beta * beta));
}

double trapezoidal_integral(double alpha, double beta, int n) {
	double a = -1.0, b = 1.0; 
	double h = (b - a) / n;   
	double sum = 0.5 * (function(a, alpha, beta) + function(b, alpha, beta));

#pragma omp parallel sections reduction(+:sum)
	{
#pragma omp section

		{
			for (int i = 1; i < n / 4; i++) {
				double x = a + i * h;
				sum += function(x, alpha, beta);
			}
		}
#pragma omp section
		{
			for (int i = n/4-1; i < n / 2; i++) {
				double x = a + i * h;
				sum += function(x, alpha, beta);
			}
		}
#pragma omp section
		{
			for (int i = n / 2 - 1; i < 3*n / 4; i++) {
				double x = a + i * h;
				sum += function(x, alpha, beta);
			}
		}
#pragma omp section
		{
			for (int i = 3*n / 4 - 1; i < n; i++) {
				double x = a + i * h;
				sum += function(x, alpha, beta);
			}
		}


	}


	return sum * h;
}

int main() {
	double alpha, beta;
	int n = 100000000;
	setlocale(LC_ALL, "RU");
	cout << "Введите значения alpha и beta (0 < alpha, beta < 1): ";
	cin >> alpha >> beta;
	double t = omp_get_wtime();


	double result = trapezoidal_integral(alpha, beta, n);
	cout << "Приближенное значение интеграла: " << result << endl;
	cout << "Time: " << omp_get_wtime() - t << endl;

	return 0;
}
