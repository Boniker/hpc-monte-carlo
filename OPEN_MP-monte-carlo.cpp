#include <iostream>
#include <sstream>
#include <ctime>
#include <omp.h>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <math.h>
                                                                                                                                           
using namespace std;
                                                                                                                                           
double fRand(double fMin, double fMax)
{                                                                                                                                          
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}                                                                                                                                          
                                                                                                                                           
int main(int argc, char *argv[])
{                                                                                                                                          
    srand(time(NULL));
    double R;
    int N;
    int numberOfThreads;
                                                                                                                                           
A:
    stringstream(argv[1]) >> numberOfThreads;
    stringstream(argv[2]) >> R;
    stringstream(argv[3]) >> N;
    cout << "\nnumberOfThreads = " << numberOfThreads << "\nR = " << R << "\nLog(N) = " << N << endl;
    long precision = pow(2, N);
    cout << "Precision (2^N) = " << precision << endl;
    omp_set_num_threads(numberOfThreads);                                                                                                  
    double start = omp_get_wtime();
    int m = 0;
                                                                                                                                           
#pragma omp parallel for reduction(+:m)
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
cout << "Expected result: " << 4.0 / 3 * M_PI * R * R * R << endl;
                                                                                                                                           
return 0;
}
