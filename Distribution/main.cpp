#include <iostream>
#include <cmath>

using namespace std;

int factorial(int n){
    if(n == 1){
        return 1;
    }
    if(n == 0){
        return 1;
    }
    return n * factorial(n -1);

}

double binomialCoefficient(int n, int r){
    double numerator = 1;
    double k = n - r;
    for(int i=n; i>k; i--){
        numerator *= i;
    }
    return numerator / factorial(r);
}

double binomialProbabilityDistribution(int n, double p, int k){

    return binomialCoefficient(n, k) * pow(p, k) * pow(1-p, n-k);

}

double binomialCumulativeDistribution(int n, double p, int k, int l){
    double result = 0;
    for(int i=k; i<l; i++){
        result += binomialProbabilityDistribution(n, p, i);

    }
    return result;
}

int main()
{
    cout << binomialCoefficient(6, 2) <<endl;
    cout << binomialCumulativeDistribution(7, 0.35, 0, 5);

    return 0;
}
