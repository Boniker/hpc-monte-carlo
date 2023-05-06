// OpenMP_Monte-Carlo.cpp : This file contains the 'main' function. Program execution begins and ends there.
# include <iostream>
# include <ctime>
# include <omp.h>
# include <cstdlib>
# include <iomanip>
# include <cmath>
# include <ctime>

using namespace std;

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int main()
{
	srand(time(NULL));
	double R;
	int N;
	const double pi = 3.14159265358979323846;
	int numberOfThreads;

A:

	cout << "Number of threads = ";
	cin >> numberOfThreads;

	cout << "R = ";
	cin >> R;

	cout << "Log(N) = ";
	cin >> N;

	long precision = pow(2, N);

	cout << "Precision (2^N) = " << precision << endl;

	omp_set_num_threads(numberOfThreads);

	double start = omp_get_wtime();
	int m = 0;

#pragma omp parallel for
	for (int i = 0; i < precision; ++i)
	{
		double x = fRand(-R, R);
		double y = fRand(-R, R);
		double z = fRand(-R, R);
		if (x * x + y * y + z * z < R * R) m++;
	}

	double end = omp_get_wtime();
	double time = end - start;
	cout << "\n";
	cout << "OmpTime:" << setprecision(8) << time << endl;
	cout << "Calculation result: " << (double)m / precision * 8 * R * R * R << endl;
	cout << "Expected result: " << 4.0 / 3 * pi * R * R * R << endl;

	char answer;

	cout << "For starting over enter '*': ";
	cin >> answer;
	if (answer == '*') {
		cout << "------------------------------" << endl;
		cout << "\n";
		goto A;
	}

	return 0;
}