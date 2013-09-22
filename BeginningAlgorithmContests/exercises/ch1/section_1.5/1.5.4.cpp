#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

int main()
{
    int a=0,b=1,c=1,x=1,y=1;
    printf("%d\n", a&&b||c);
    if(a)
     if(b) x++;
     else y++;
    printf("%d %d %d %d\n", a,b,x,y);
    
    printf("%d %d\n", INT_MAX, INT_MIN);
    printf("%ld %ld\n", LONG_MAX, LONG_MIN);
    printf("%e %e\n", FLT_MAX, FLT_MIN);
    printf("%e %e\n", DBL_MAX, DBL_MIN);
    return 0;
}
