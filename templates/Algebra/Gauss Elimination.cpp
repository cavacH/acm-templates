#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define LL long long
#define mem(x, y) memset(x, y, sizeof(x))
#define pii pair<int, int>
#define mkp make_pair
const int N = 505;
const double eps = 1e-8;
double a[N][N], x[N];

int Gauss(int row, int col) {
    for(int i = 0, j = 0; i < row && j < col - 1; i++, j++) {
        int mx_row = i;
        for(int k = i + 1; k < row; k++) {
            if(fabs(a[k][j]) > fabs(a[mx_row][j])) mx_row = k;
        }
        for(int k = j; k < col; k++) swap(a[i][k], a[mx_row][k]);
        if(fabs(a[i][j]) < eps) {
            i--;
            continue;
        }
        for(int k = i + 1; k < row; k++) {
            if(fabs(a[k][j]) < eps) continue;
            double mul = -a[i][j] / a[k][j];
            for(int l = j; l < col; l++) a[k][l] = a[k][l] * mul + a[i][l];
        }
    }
    for(int i = 0; i < row; i++) {
        bool not_zero = 0;
        for(int j = 0; j < col - 1; j++) not_zero |= (fabs(a[i][j]) > eps);
        if(!not_zero && fabs(a[i][col - 1]) > eps) return 0;
    }
    for(int i = row - 1; i >= 0; i--) {
        double right = a[i][col - 1];
        for(int j = i + 1; j < col - 1; j++) right -= a[i][j] * x[j];
        x[i] = right / a[i][i];
    }
    return 1;
}

int main()
{
    a[0][0] = a[0][1] = 1;
    a[0][2] = 3;
    a[1][0] = 1;
    a[1][1] = -1;
    a[1][2] = 5;
    cout << Gauss(2, 3) << endl;
    cout << x[0] << " " << x[1] << endl;
    return 0;
}



