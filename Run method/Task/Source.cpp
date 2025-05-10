#include <iostream>
#include <cmath>
#include <omp.h>


void run_method(int n, double* a, double* b, double* c, double* d, double* x) {
    double* A = new double[n];
    double* B = new double[n];
    double* e = new double[n];

    A[0] = -c[0] / b[0];
    B[0] = d[0] / b[0];
    e[0] = b[0];

#pragma omp parallel for

    for (int i = 1; i < n - 1; ++i) {
        e[i] = a[i] * A[i - 1] + b[i];
        A[i] = -c[i] / e[i];
        B[i] = (d[i] - a[i] * B[i - 1]) / e[i];
    }

    e[n - 1] = a[n - 1] * A[n - 2] + b[n - 1];
    x[n - 1] = (d[n - 1] - a[n - 1] * B[n - 2]) / e[n - 1];
#pragma omp parallel for

    for (int i = n - 2; i >= 0; --i) {
        x[i] = A[i] * x[i + 1] + B[i];
    }


}

int main() {


    int n = 3;

    double c[] = { 1, 1, 0 };   // наддиагональ 
    double b[] = { 2, 3, 2 };   // главная диагональ
    double a[] = { 0, 1, 1 };   // поддиагональ 
    double d[] = { 4, 10, 8 };   // правые части

    double* x = new double[n]; // решение
    double t = omp_get_wtime();
    run_method(n, a, b, c, d, x);

    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << std::endl;
    }
    std::cout << "Time: " << omp_get_wtime() - t << std::endl;

    return 0;
}