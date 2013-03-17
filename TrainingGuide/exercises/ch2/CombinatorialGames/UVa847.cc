// UVa847 A multiplication game
// 陈锋
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;
typedef long long int64;
const int64 maxn = 4294967295;
int64 n;
vector<int64> seg;

// bool solve(int64 p)
// {
    // assert(p < n);
    // for(int i = 2; i <= 9; i++)
    // {
        // int64 next = p*i;
        // if(next >= n || solve(next) == false) return true;
    // }
    // return false;
// }

// void runcase()
// {
    // bool ans = solve(1);    
    // cout<<(ans ? "Stan wins." : "Ollie wins.")<<endl;
// }

int64 pow(int64 base, int i)
{
    if(i == 0) return 1;
    int64 ans = pow(base, i / 2);
    ans *= ans;
    if(i % 2) ans *= base;
    return ans;
}

int main()
{    
    int i = 1;
    while(true)
    {
        int64 left = pow(3, 2*i) * pow(2,i-1) + 1;
        if(left > maxn) break;            
        int64 right  = left * 2 - 2;
        seg.push_back(left);
        seg.push_back(right);
        i++;
    }

    while(cin>>n)
    {
        int i = 0;
        while(true)
        {            
            if(n <= seg[i]) break;
            i++;
        }
        
        bool ans;
        if(seg[i] == n) ans = false;
        else ans = (i % 2 == 0);
        
        cout<<(ans ? "Stan wins." : "Ollie wins.")<<endl;
    }
    return 0;
}
