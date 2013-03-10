// UVa10127 Ones
// 陈锋
#include<cstring>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long longInt;

longInt n;

void runcase()
{
    longInt i = 1, ans = 1, mod;
    while(true)
    {
        mod = i % n;
        if(mod == 0) break;
        ans++;
        i = mod * 10 + 1;
    }

    cout<<ans<<endl;
}

int main() {
    while(cin>>n)
    {
        runcase();
    }
    return 0;
}