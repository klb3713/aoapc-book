// UVa10061 How many zero's and how many digits?
// 陈锋
#include<cstring>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<climits>
using namespace std;
typedef long long longInt;
const int MAXB = 800 + 10;
longInt N, B, f[MAXB], f2[MAXB];

longInt getDigits()
{
    double sum = 0;
    for(longInt i = 1; i <= N; i++)
        sum += log10(i);
    return floor( sum / log10(B) + 1e-9) + 1;
}

longInt getZeroCount()
{
    fill_n(f, B + 1, 0);
    fill_n(f2, B + 1, 0);
    // 先对B做唯一分解
    longInt B2 = B;
    for(int i = 2; i <= B; i++)
    {
        while(B2 % i == 0)
        {
            f[i]++;
            B2 /= i;
        }
    }

    
    for(longInt i = 2; i <= N; i++)
    {
        longInt i2 = i;
        for(int j = 2; j <= B; j++)
        {
            while(i2 % j == 0)
            {
                f2[j]++;
                i2 /= j;
            }
        }
    }
    
    longInt ans = LONG_MAX;
    for(int i = 2; i <= B; i++)
    {        
        if(f[i] != 0)
            ans = min(ans, f2[i] / f[i]);
    }
    
    return ans;
}

void runcase()
{    
    cout<<getZeroCount()<<" "<<getDigits()<<endl;
}

int main() {
    while(cin>>N>>B)
    {
        runcase();
    }
    return 0;
}