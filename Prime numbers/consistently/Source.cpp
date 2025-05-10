#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
using namespace std;

bool prime(int n)
{
	if (n % 2 == 0)
		return false;
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
	for (int i = 3; i < n; i = i + 2)
	{
		if (prime(i) == true)
		{
			sum = sum + 1;
		}
	}

	return sum;
}

int main()
{
	int n = 100000000;
	double t = omp_get_wtime();

	int count = prime_numbers(n);

	cout << "Number: " << count << endl;
	cout << "Time: " << (omp_get_wtime() - t) << endl;

	return EXIT_SUCCESS;
}