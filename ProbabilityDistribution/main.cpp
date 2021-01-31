#include <iostream>
#include <cmath>

using namespace std;

int factorial(int n){
    if(n == 0){
        return 1;
    }
    if(n == 1){
        return 1;
    }else{
        return n * factorial(n - 1);
    }
}


double binomialCoefficient(int n, int k){
    double numerator = 1;
    int r = n - k;
    for(int i=n; i>r; i--){
        numerator *= i;
    }
    return numerator / factorial(k);
}


double binomialProbabilityDistribution(int n, double p, int k){
    return binomialCoefficient(n, k) * pow(p, k) * pow(1-p, n-k);
}


double binomialCumalativeDistribution(int n, double p, int minRange, int maxRange){
    double result = 0;
    for(int i=minRange; i<=maxRange; i++){
        result += binomialProbabilityDistribution(n, p, i);
    }
    return result;
}

double geometricProbabilityDistribution(double p, int n){
    double result = 1;
    for(int i=1; i<n; i++){
        result *= 1-p;
    }
    result *= p;
    return result;
}

double geometricCumlativeDistribution(double p, int minRange, int maxRange){
    double result = 0;
    for(int i=minRange; i<=maxRange; i++){
        result += geometricProbabilityDistribution(p, i);
    }
    return result;
}

int main()
{

    double f = geometricProbabilityDistribution(0.15, 6);
    cout << f <<endl;
    return 0;
}

