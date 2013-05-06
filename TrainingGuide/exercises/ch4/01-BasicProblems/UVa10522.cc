// UVa10522 Height to Area
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
const double eps = 1e-8;
double dcmp(double x) { if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
bool valid(double x){ return dcmp(x) > 0; }

int main()
{
    int n, c = 0;
    scanf("%d", &n);
    double x, y, z;
    while(true)
    {    
        scanf("%lf%lf%lf",&x,&y,&z);
        // printf("%.3lf %.3lf %.3lf\n",x,y,z);
        bool v = valid(x) && valid(y) && valid(z);        
        if(v)
        {
            double p = (1/x+1/y+1/z)*(1/y+1/z-1/x)*(1/x+1/z-1/y)*(1/x+1/y-1/z);
            v = valid(p);
            // printf("p = %g, ", p);
            if(v){ printf("%.3lf\n", 1/sqrt(p)); continue; }
        }
        
        c++;
        puts("These are invalid inputs!");
        if(c == n) break;
    }
}
