#include <iostream>
#include <cmath>
#define N 2

using namespace std;

struct VectStruct{
    double vect[N];
};

class Vector {
    public:
        Vector(){}

        double magnitude(double vectr[N]){
            double temp = 0;
            for(int i=0; i<N; i++){
                temp += vectr[i] * vectr[i];
            }
            double result = sqrt(temp);
            return result;
        }


        double dotProduct(double vect1[N], double vect2[N]){
            double result = 0;
            for(int i=0; i<N; i++){
                result += vect1[i] * vect2[i];
            }
            return result;
        }


        VectStruct scaleVector(double scalar, double vectr[N]){
            VectStruct result;
            for(int i=0; i<N; i++){
                result.vect[i] = vectr[i] * scalar;
            }
            return result;
        }


        //projection of a vector on to a line
        //projection of x on to v
        VectStruct projection(double x[N], double v[N]){
            if(N==2){
                VectStruct result;
                double scalarVal = dotProduct(x, v) / magnitude(v);
                result = scaleVector(scalarVal, v);
                return result;
            }
        }
};

int main()
{
    double v1[N] = {1,2};
    double v2[N] = {1,1};
    Vector vect1;

    VectStruct v;
    v = vect1.projection(v1, v2);
    for(int i=0; i<N; i++){
        cout << v.vect[i]<<endl;
    }
    return 0;
}
