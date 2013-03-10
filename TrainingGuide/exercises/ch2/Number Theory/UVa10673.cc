// UVa10673 Play with Floor and Ceil 
// ³Â·æ
#include<cstring>
#include<iostream>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<cstdio>
using namespace std;
long long N;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}

void gcd(int a, int b, int& d, int& x, int& y)
{
    if(b == 0) 
    {
        d = a; x = 1; y = 0;
    }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= x * (a/b);
    }
}

void runcase(int t)
{
    int x, k, a, b, d;
    cin>>x>>k;
    a = x / k, b = a;
    
    if(x % k != 0) b++;
    int p0, q0;
    gcd(a, b, d, p0, q0);
    // printf("a = %d, b = %d, d = %d, p0 = %d, q0 = %d\n", a,b,d,p0,q0);
    
    assert(x % d == 0);
    p0 *= (x / d);
    q0 *= (x / d);
    cout<<p0<<" "<<q0<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T;
    cin>>T;
    for(int t = 0; t < T; t++)
    {
        runcase(t);
    }
    return 0;
}