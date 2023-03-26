#include <iostream>
#include <cmath>
using namespace std;

double f1(double x1, double x2, double x3) { return (double) 1 / 3 * (x2 - 2*x3 + 1); }
double f2(double x1, double x2, double x3) { return 0.5 * (x1 - 0.5 * x3 + 2); }
double f3(double x1, double x2, double x3) { return (double) 1 / 3 * (-2*x1 - 0.5 * x2 + 3); }

void SeidelMethodSolve(double Eps) {
    double x01 = 0, x02 = 0, x03 = 0;
    double x11, x22, x33;
    double e1, e2, e3, e;
    int i = 1;
//    cout << "Determinant of Matrix A = 4.25" << endl;
//    cout << "Condition number = 20.11" << endl;
    do {
        x11 = f1(x01, x02, x03);
        x22 = f2(x01, x02, x03);
        x33 = f3(x01, x02, x03);
        cout << i << "-th iteration: " << x11 << ", " << x22 << ", " << x33 << endl;
        e1 = abs(x01 - x11);
        e2 = abs(x02 - x22);
        e3 = abs(x03 - x33);
        e = sqrt(e1 * e1 + e2 * e2 + e3 * e3);
        if (i == 1)
            cout << "Euclid norm: ||(" << x11 << "," << x22 << "," << x33 << ")T-(" << x01 << "," << x02 << ","
                      << x03 << ")T|| = " << e << endl;
        if (e < Eps) break;
        x01 = x11;
        x02 = x22;
        x03 = x33;
        i++;
    } while (e > Eps);
    cout << "Euclid norm: ||(" << x11 << "," << x22 << "," << x33 << ")T-(" << x01 << "," << x02 << "," << x03
              << ")T|| = " << e << endl;
    cout << "The found soulution:" << endl;
    cout << "x1 = " << x11 << endl;
    cout << "x2 = " << x22 << endl;
    cout << "x3 = " << x33 << endl;
}