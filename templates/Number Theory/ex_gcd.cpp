#include<bits/stdc++.h>
using namespace std;

#define LL long long

/**
    calculate gcd(a,b) and a pair of (x,y) satisfy ax + by = gcd(a,b)
**/

LL ex_gcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL res = ex_gcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return res;
}

int main()
{
    return 0;
}
