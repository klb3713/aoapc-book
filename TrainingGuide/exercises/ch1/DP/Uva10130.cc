// Uva10130	SuperSale
// 陈锋
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline bool isnum(char c)
{
    return c >= '0' && c <= '9';
}

inline int readint()
{
    char c = getchar();    
    while(!isnum(c)) c = getchar();
    
    int data = c - '0';
    while(isnum(c = getchar())) data = data * 10 + c - '0';
    
    return data;
}

const int MAXN = 1024, MAXG = 320;

int P[MAXN], W[MAXN], MW[MAXG], D[32][MAXN];

// n - 待选的物品数量，w - 剩余的重量
// 返回最大可能的价格
int dp(int w, int n)
{
    int& ans = D[w][n];
    if(ans != -1) return ans;
    
    if(w == 0 || n == 0) return ans = 0;
    
    if(w < W[n-1]) return ans = dp(w, n - 1);
    
    return ans = max(P[n-1] + dp(w - W[n-1], n - 1), dp(w, n - 1));
}

int main()
{
    int T = readint();
    while(T--)
    {
        int i, N, G;
        N = readint();
        for(i = 0; i < N; i++)
        {
            P[i] = readint();
            W[i] = readint();
        }
        
        memset(D, -1, sizeof(D));
        int ans = 0;
        G = readint();
        for(i = 0; i < G; i++)
            ans += dp(readint(), N);
        printf("%d\n", ans);
    }
    return 0;
}
