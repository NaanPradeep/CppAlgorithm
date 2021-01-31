#include <iostream>
#define N 3
#define M 4


using namespace std;

struct Arrstruct
{
    double arr[N][N];
};

struct Arrstruct2
{
    double arr1[N][M];

};

class Matrix {

    public:
        double rows[N][N];
        Matrix(double m[N][N]){
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    rows[i][j] = m[i][j];
                }
            }
        }
        ~Matrix(){}


        Arrstruct identityMatrix(){
            Arrstruct idenMatrix;
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if(i == j){
                        idenMatrix.arr[i][j] = 1;
                    }else{
                        idenMatrix.arr[i][j] = 0;
                    }
                }
            }
            return idenMatrix;
        }

        Arrstruct copyMatrix(){
            Arrstruct rowMatrix;
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    rowMatrix.arr[i][j] = rows[i][j];
                }
            }
            return rowMatrix;
        }

        //determinantSwap() will change the sign of the changed row(row2)
        void determinantSwap(double dMatrix[N][N], double tempMatrix[2][N], int row1, int row2){
            // Two swapping rows ---> tempMatrix
            for(int m=0; m<N; m++){
                tempMatrix[0][m] = dMatrix[row1][m];
                tempMatrix[1][m] = dMatrix[row2][m];
            }
            // tempMatrix ---> swapping rows in dMatrix
            for(int n=0; n<N; n++){
                dMatrix[row1][n] = -1 * tempMatrix[1][n];
                dMatrix[row2][n] = tempMatrix[0][n];
            }
        }


        Arrstruct upperTriangularMatrix(){
            Arrstruct dMatrix;
            dMatrix = copyMatrix();
            //Changing our square matrix to upper Triangular Matrix
            for(int k=0; k<N-1; k++){
                for(int i=k+1; i<N; i++){
                    //If pivot element is zero
                    if(dMatrix.arr[k][k] == 0){
                        for(int m=k+1; m<N; m++){
                            if(dMatrix.arr[m][k] != 0){
                                double tempMatrix[2][N];//To store two rows to be swapped
                                determinantSwap(dMatrix.arr, tempMatrix, k, m);//swapping rows to change the pivot element
                                break;
                            }
                        }
                    }
                    if(dMatrix.arr[i][k] == 0){
                        continue;
                    }
                    double factor = dMatrix.arr[i][k] / dMatrix.arr[k][k];
                    for(int j=k; j<N; j++){
                        dMatrix.arr[i][j] = dMatrix.arr[i][j] - factor * dMatrix.arr[k][j];
                    }
                }
            }
            return dMatrix;
        }


        double determinantOfAMatrix(){
            Arrstruct uTM;
            uTM = upperTriangularMatrix();
            int det = 1;

            for(int s=0; s<N; s++){
                det *= uTM.arr[s][s];
            }
            return det;

        }


        void inverseSwap(double iMatrix[N][N], double idenMatrix[N][N], int fRow, int sRow){
            double tempMatrix1[2][N];
            double tempMatrix2[2][N];
            for(int i=0; i<N; i++){
                tempMatrix1[0][i] = iMatrix[fRow][i];
                tempMatrix1[1][i] = iMatrix[sRow][i];

                tempMatrix2[0][i] = idenMatrix[fRow][i];
                tempMatrix2[1][i] = idenMatrix[sRow][i];
            }
            for(int m=0; m<2; m++){
                for(int n=0; n<N; n++){
                    if(m == 0){
                        iMatrix[sRow][n] = tempMatrix1[m][n];
                        idenMatrix[sRow][n] = tempMatrix2[m][n];
                    }else{
                        iMatrix[fRow][n] = tempMatrix1[m][n];
                        idenMatrix[fRow][n] = tempMatrix2[m][n];
                    }
                }
            }
        }


        Arrstruct inverseOfAMatrix(){
            Arrstruct iMatrix;
            iMatrix = copyMatrix();
            Arrstruct idenMatrix;
            idenMatrix = identityMatrix();
            for(int k=0; k<N; k++){
                if(iMatrix.arr[k][k] == 0){
                    for(int n=k+1; n<N; n++){
                        if(iMatrix.arr[n][k] != 0){
                            inverseSwap(iMatrix.arr, idenMatrix.arr, k, n);//Swapping rows if pivot is zero
                            break;
                        }
                    }
                }
                double pivot = iMatrix.arr[k][k];
                //Dividing pivot in the k th row of a iMatrix
                for(int n=k; n<N; n++){
                    iMatrix.arr[k][n] = iMatrix.arr[k][n] / pivot;
                }
                //Dividing pivot in the k th row of a idenMatrix
                for(int m=0; m<N; m++){
                    idenMatrix.arr[k][m] = idenMatrix.arr[k][m] / pivot;
                }

                for(int i=0; i<N; i++){
                    if(iMatrix.arr[i][k] == 0){//Skipping when non pivot element is zero
                        continue;
                    }
                    if(i == k){//Ignoring the pivot element in the cloumn
                        continue;
                    }
                    double factor = iMatrix.arr[i][k];
                    for(int j=0; j<N; j++){
                        iMatrix.arr[i][j] = iMatrix.arr[i][j] - factor * iMatrix.arr[k][j];
                        idenMatrix.arr[i][j] = idenMatrix.arr[i][j] - factor * idenMatrix.arr[k][j];
                    }
                }
            }
            return idenMatrix;
        }


        double dotProduct(double vect1[N], double vect2[N]){
            double result = 0;
            for(int i=0; i<N; i++){
                result += vect1[i] * vect2[i];
            }
            return result;
        }


        Arrstruct2 matrixMultiplication(double matrix1[N][N], double matrix2[N][M]){
            Arrstruct2 resultMatrix;
            double tempvect1[N];
            double tempvect2[N];

            for(int k=0; k<M; k++){
                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        tempvect1[j] = matrix1[i][j];
                        tempvect2[j] = matrix2[j][k];
                    }
                    resultMatrix.arr1[i][k] = dotProduct(tempvect1, tempvect2);
                }
            }
            return resultMatrix;
        }
};




int main()
{
    double mat[N][N] = {
                        {2,-1,5},
                        {7,4,4},
                        {6,1,-3}
                        };
    Matrix matrix1(mat);

    double maT[N][M] = {{1,2,-4,8}, {3,1,5,3}, {7,2,6,4}};
    Arrstruct2 m;
    m = matrix1.matrixMultiplication(mat, maT);



    //matrix1.someFunc();
    //double d = matrix1.determinant();
    //cout << d;
    /*Arrstruct inv;
    inv = matrix1.inverseOfAMatrix();*/
    for(int i=0; i<N; i++){
        cout << "----------------" <<endl;
        for(int j=0; j<M; j++){
            cout << m.arr1[i][j] <<endl;
        }
    }
    return 0;
}
