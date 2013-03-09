// UVa10079 Pizza Cutting
// 陈锋
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
long long N;
void runcase()
{        
    cout<<N * (N+1) / 2 + 1<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    while(true)
    {
        cin>>N;
        if(N < 0) break;
        runcase();
    }
    return 0;
}