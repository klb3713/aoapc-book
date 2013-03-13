// UVa10165    Stone Game
// 陈锋
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int main()
{
    int N;    
    while(scanf("%d", &N) == 1 && N > 0)
    {
        int ans = 0, tmp;
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &tmp);
            ans ^= tmp;
        }
        
        puts(ans == 0 ? "No" : "Yes");
    }
    
    return 0;    
}
