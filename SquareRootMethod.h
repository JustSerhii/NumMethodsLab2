#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

template<typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

vector<vector<double>> MatrixMultiplication(vector<vector<double>> a, vector<vector<double>> b) {
    vector<vector<double>> c{{0, 0, 0},
                             {0, 0, 0},
                             {0, 0, 0}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

vector<vector<double>> MatrixTranspose(vector<vector<double>> a) {
    vector<vector<double>> c{{0, 0, 0},
                             {0, 0, 0},
                             {0, 0, 0}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[i][j] = a[j][i];
        }
    }
    return c;
}

void DisplayMatrix(vector<vector<double>> Matrix) {
    for (auto list: Matrix) {
        for (auto num: list) cout << fixed << setprecision(4) << num << " ";
        cout << endl;
    }
}


void SquareRootMethodSolve() {
    vector<vector<double>> A = {{2, 1, 3},
                                {1, 2, 2},
                                {3, 2, 7.2}};
    vector<double> b = {2, 1.5, 3};

    vector<vector<double>> At = MatrixTranspose(A);
    for (int i = 0; i < 3; i++) {
        if (!equal(A[i].begin(), A[i].end(), At[i].begin())) {
            cout << "Since the matrix is not symmetrical the method cannot be applied." << endl;
            return;
        }
    }

    vector<vector<double>> S;
    vector<vector<double>> D;


    double d11 = sign(A[0][0]);
    double s11 = sqrt(abs(A[0][0]));
    double s12 = A[0][1] / d11 / s11;
    double s13 = A[0][2] / d11 / s11;

    double d22 = sign(A[1][1] - s12 * s12 * d11);
    double s22 = sqrt(abs(A[1][1] - s12 * s12 * d11));
    double s23 = (A[1][2] - s12 * d11 * s13) / (d22 * s22);

    double d33 = sign(A[2][2] - s13 * s13 * d11 - s23 * s23 * d22);
    double s33 = sqrt(abs(A[2][2] - s13 * s13 * d11 - s23 * s23 * d22));

    S = {{s11, s12, s13},
         {0,   s22, s23},
         {0,   0,   s33}};
    D = {{d11, 0,   0},
         {0,   d22, 0},
         {0,   0,   d33}};
    cout << "Matrix S:" << endl;
    DisplayMatrix(S);
    cout << "Matrix D:" << endl;
    DisplayMatrix(D);

    vector<vector<double>> st = MatrixTranspose(S);
    vector<vector<double>> std = MatrixMultiplication(st, D);
    double y1 = b[0] / std[0][0];
    double y2 = (b[1] - std[1][0] * y1) / std[1][1];
    double y3 = (b[2] - std[2][0] * y1 - std[2][1] * y2) / std[2][2];

    double x3 = y3 / S[2][2];
    double x2 = (y2 - S[1][2] * x3) / S[1][1];
    double x1 = (y1 - S[0][1] * x2 - S[0][2] * x3) / S[0][0];

    double det = d11 * s11 * s11 * d22 * s22 * s22 * d33 * s33 * s33;
    cout << "Determinant of matrix A = " << det << endl;
    cout << "The found solution:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "x3 = " << x3 << endl;
}