// UVa10347 Medians
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

double x, y, z;

bool check(double a, double b, double c){
    if(a >= b + c || a < fabs(b - c)) return false;
    return true;
}

// http://jwilson.coe.uga.edu/emt725/Medians.Triangle/Area.Medians.Tri.html
void solve()
{
    if(x > 0 && y > 0 && z > 0 &&
        check(x, y, z) && check(y, x, z) && check(z, x, y))
    {
        x *= x;
        y *= y;
        z *= z;
        double ans = sqrt( 2 * (x * y + x * z + y * z) - (x*x + y*y + z*z) ) / 3;
        printf("%.3lf\n", ans);
        return;
    }
    puts("-1.000");
}

int main()
{
    while(scanf("%lf%lf%lf",&x,&y,&z) == 3){
        solve();
    }
    return 0;
}
