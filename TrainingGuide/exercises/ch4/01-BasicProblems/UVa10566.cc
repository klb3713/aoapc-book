// UVa10566 Crossed Ladders
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;
double x, y, c;
inline double F(double u){ return c/sqrt(x*x - u*u) + c/sqrt(y*y - u*u) - 1;}

int main()
{
    while(scanf("%lf%lf%lf",&x,&y,&c) == 3)
    {   
        double R = min(x, y), L = 0, M;
        // while(dcmp(L - R))
        for(int i = 0;i<100;i++)
        {  
            M = (L + R) / 2;
            double f = F(M);
            if(f == 0.0) break;
            else if(f > 0) R = M; 
            else L = M;
        }  
        printf("%.3lf\n", M);
    }
}
