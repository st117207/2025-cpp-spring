#include <iostream>
#include <future>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <chrono>
using namespace std::chrono;
double function(double x, double alpha, double beta) {
	return 1.0 / (sqrt(1 - 2 * alpha * x + alpha * alpha) * sqrt(1 - 2 * beta * x + beta * beta));
}

double trapezoidal_integral(double a, double b, double alpha, double beta, int n) {
	double h = abs(b - a) / n;
	double sum = 0.5 * (function(a, alpha, beta) + function(b, alpha, beta));

	for (int i = 1; i < n; i++) {
		double x = a + i * h;
		sum += function(x, alpha, beta);
	}

	return sum * h;
}


int main() {
	setlocale(LC_ALL, "ru");
	const int n = 100000000; // Общее число итерация
	const double num_threads = 12.0;      // Количество потоков
	double length = 2 / num_threads;
	double alpha = 0;
	double beta = 0;
	std::cout << "Введите значения alpha и beta (0 < alpha, beta < 1): ";
	std:: cin >> alpha >> beta;
	std::vector<std::future<double>> futures;
	
	auto t1 = steady_clock::now();
	double start = -1;
	for (int i = 0; i < num_threads; i++) {
		double end = (i == num_threads - 1) ? 1 : start + length;
		futures.push_back(std::async(trapezoidal_integral, start, end, alpha, beta, n));
		start = end;

	}

	double value = 0.0;
	for (auto& future : futures) {
		value += future.get();
	}
	auto t2 = steady_clock::now();

	std::cout << "Value: " << value << std::endl;
	std::cout << duration_cast<seconds> (t2 - t1).count() << " s " << std::endl;

	return 0;
}