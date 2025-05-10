#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
using namespace std;

bool prime(int n)
{

	for (int i = 3; i * i <= n; i = i + 2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

double prime_numbers(int n)
{
	int sum = 0;
#pragma omp parallel sections reduction(+:sum)
	{
#pragma omp section
		{
			for (int i = 3; i < 0.63*n; i = i + 2)
			{
				if (prime(i) == true)
				{
					sum = sum + 1;
				}
			}
		}
#pragma omp section
		{
			for (int i = 0.63*n+1; i < n; i = i + 2)
			{
				if (prime(i) == true)
				{
					sum = sum + 1;
				}
			}
		}
	}


	return sum;
}

int main()
{
	int n = 10000000;
	double t = omp_get_wtime();

	int count = prime_numbers(n);

	cout << "Number: " << count << endl;
	cout << "Time: " << (omp_get_wtime() - t) << endl;

	return EXIT_SUCCESS;
}