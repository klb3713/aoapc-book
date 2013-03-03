// Uva10817	Headmaster's Headache
// 陈锋
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#include <cstdio>

using namespace std;

int readint()
{
    int num;
    scanf("%d", &num);
    return num;
}

const int MAXS = 8, MAXM = 20, MAXN = 100;

struct Teacher // 候选教师
{
    int cost;
    bool subjects[MAXS];
    
    void readline()
    {
        cost = readint();
        fill_n(subjects, MAXS, false);
        char c;
        c = getchar();
        while(c != '\n')
        {
            if(isdigit(c)) subjects[c - '1'] = true; 
            c = getchar();
        }
    }
};

int S, M, N, subgap[MAXS]; // 学科还缺的教师数量
Teacher Servings[MAXM], Cands[MAXN];
int DP[MAXN + 1][6562]; // 3^8 + 1
int VIS[MAXN + 1][6562];

inline int get_sub_state()
{
    int state = 0;
    for(int i = 0; i < S; i++) state = state * 3 + max(subgap[i], 0);
    return state;
}

int dp(int i)
{
    int state = get_sub_state();
    int& ans = DP[i][state];
    if(VIS[i][state]) return ans;
    
    if(i > 0)
    {
        // 选上第i个
        for(int j = 0; j < S; j++) if(Cands[i-1].subjects[j]) subgap[j]--;
        
        ans = dp(i-1);
        if(ans >= 0) ans += Cands[i-1].cost;
        
        // 去掉第i个
        for(int j = 0; j < S; j++) if(Cands[i-1].subjects[j]) subgap[j]++;
        
        // 不选第i个
        int ans2 = dp(i-1);
        if(ans >= 0)
        {
            if(ans2 >= 0) ans = min(ans, ans2);
        }
        else
            ans = ans2;
    }
    else
    {
        ans = 0;
        for(int j = 0; j < S; j++)
        {
            if(subgap[j] > 0)
            {
                ans = -1;
                break;
            }
        }
    }
    
    VIS[i][state] = 1;
    return ans;
}

int main()
{
    while(true)
    {
        int i, j, cost;
        S = readint();
        if(S == 0) break;
        M = readint(), N = readint();
        memset(DP, 0, sizeof(DP));
        memset(VIS, 0, sizeof(VIS));
        fill_n(subgap, MAXS, 2);
        
        cost = 0;
        for(i = 0; i < M; i++) 
        {
            Servings[i].readline();
            cost += Servings[i].cost;
            for(j = 0; j < S; j++) if(Servings[i].subjects[j]) subgap[j]--;
        }
        
        for(int j = 0; j < S; j++) if(subgap[j] < 0) subgap[j] = 0;
        
        for(i = 0; i < N; i++) Cands[i].readline();
        
        printf("%d\n", cost + dp(N));
    }
    
    return 0;
}
