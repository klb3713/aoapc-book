// UVa10110 Light, more light
// ³Â·æ
#include<cstring>
#include<iostream>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<cstdio>
using namespace std;

typedef unsigned long long longInt;
longInt n;

void runcase()
{    
    longInt s = (longInt)sqrt((double)n);
    if(s * s == n) cout<<"yes";
    else cout<<"no";
    cout<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    while(true)
    {
        cin>>n;
        if(n == 0) break;
        runcase();
    }
    return 0;
}