// UVa1333(LA3147) Model Rocket Height
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cfloat>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

double read_double()
{
    double x;
    scanf("%lf", &x);
    return x;
}
const double PI = acos(-1.0);

double sin2d(double d) {
    double s = sin(d * PI / 180.0);
    return s * s;
}

int main()
{
    const double D = read_double(), H = read_double();
    double A, B, C;
    
    while(true) {
        A = read_double(), B = read_double(), C = read_double();
        if(dcmp(A) <= 0 || dcmp(B) <= 0 || dcmp(C) <= 0) break;
        
        double x = D / sqrt( 0.5 / sin2d(A) + 0.5 / sin2d(C) - 1 / sin2d(B));
        x += H;
        printf("%g\n", floor(x + .5));
    }
    return 0;
}