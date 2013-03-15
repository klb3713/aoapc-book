// UVa 12293 Box Game
// 陈锋
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long int64;


// 大盒子里面有n个球，是否有必胜策略？
bool solve(int64 n)
{
    return ((n+1)&n) != 0;

    // if(n == 1) return false;
    
    // for(int i = n/2 + n%2; i < n; i++)
        // if(!solve(i)) return true;
    // return false;
}

int main()
{    
    int64 n;
    while(true)
    {
        scanf("%lld", &n);
        if(n == 0) break;
        puts(solve(n) ? "Alice" : "Bob");
    }
    return 0;    
}
