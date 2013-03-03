// Uva10243	Fire! Fire!! Fire!!!
// 陈锋
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

inline bool isnum(char c)
{
    return c >= '0' && c <= '9';
}

inline int readint()
{
    char c = getchar();    
    while(!isnum(c)) c = getchar();
    
    int data = 0;
    while(isnum(c))
    {
        data = data * 10 + c - '0';
        c = getchar();
    }
    
    return data;
}

const int MAXN = 1024;
typedef vector<int>::iterator INTITER;

int N, DP[MAXN][2], LEVEL[MAXN];
vector<int> G[MAXN];

// DP[i][1] 表示i 选上了的话，以i为根的子树上最少需要选多少个
// DP[i][0] 表示i 不选的话，以i为根的子树上最少需要选多少个
// 状态方程
// dp[i][1] = Σ（j ∈ i的子节点） min(dp[j][1],dp[j][0])
// dp[i][0] = Σ（j ∈ i的子节点） dp[j][1]

int dp(int i, int selected)
{
    int& ans = DP[i][selected];
    if(ans) return ans;
    ans = selected;
    
    int l = LEVEL[i];
    vector<int>& children = G[i];
    for(INTITER ci = children.begin(); ci != children.end(); ci++)
    {
        int c = *ci;
        if(LEVEL[c] == l + 1)
        {
            int cans = dp(c, 1);
            if(selected) cans = min(cans, dp(c, 0));
            ans += cans;
        }
    }
    
    return ans;
}

void setlevel(int i)
{
    int nl = LEVEL[i] + 1;
    vector<int>& v = G[i];
    INTITER it;
    for(it = v.begin(); it != v.end(); it++)
        if(LEVEL[*it] == -1) LEVEL[*it] = nl;
        
    for(it = v.begin(); it != v.end(); it++)
        if(LEVEL[*it] == nl) setlevel(*it);
}

int main()
{
    int i, ni;
    for(i = 0; i < MAXN; i++) G[i].reserve(MAXN);
    
    while(true)
    {
        N = readint();
        if(N == 0) break;
        
        fill_n(LEVEL, MAXN, -1);
        for(i = 0; i < N; i++)
        {
            G[i].clear();
            ni = readint();
            while(ni--) G[i].push_back(readint() - 1);            
        }
        
        memset(DP, 0, sizeof(DP));
        fill_n(LEVEL, MAXN, -1);
        
        LEVEL[0] = 0;
        setlevel(0);
        
        printf("%d\n", N == 1 ? 1 : min(dp(0,0), dp(0,1)));
    }
    
    return 0;
}