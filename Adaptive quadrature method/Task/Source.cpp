#include <iostream>
#include <cmath>
#include <cstdlib>
#include <omp.h>

using namespace std;

double function(double x) {
    double alpha = 0.3;
    double beta = 0.4;
    return 1.0 / (sqrt(1 - 2 * alpha * x + alpha * alpha) * sqrt(1 - 2 * beta * x + beta * beta));
}


double integr(double a, double b, double (*func)(double), int n = 10) {
    double h = (b - a) / n;
    double value = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; i++) {
        value += func(a + i * h);
    }

    return value * h;
}

double integral(double a, double b, double (*func)(double), double ris = 1e-10) {
    double full_integral = integr(a, b, func);
    double middle = (a + b) / 2.0;
    double left_integral = integr(a, middle, func);
    double right_integral = integr(middle, b, func);

    if (abs(full_integral - (left_integral + right_integral)) <= ris) {
        return full_integral;
    }
    else {
        return integral(a, middle, func, ris) + integral(middle, b, func, ris);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    double t = omp_get_wtime();
    double alpha = 0.3;
    double beta = 0.4;

    double result = integral(-1, 1, function);
    cout << "Правильное значение: " << 1 / sqrt(alpha * beta) * log((1 + sqrt(alpha * beta)) / (1 - sqrt(alpha * beta))) << endl;
    cout << "Приближенное значение интеграла: " << result << endl;
    cout << "Time: " << omp_get_wtime() - t << endl;

    return 0;
}