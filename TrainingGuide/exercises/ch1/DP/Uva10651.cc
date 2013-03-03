// Uva10651	Pebble Solitaire
// 陈锋
#include <cstring>
#include <cstdio>
#include <bitset>
#include <algorithm>

using namespace std;

const int LEN = 12;
typedef bitset<LEN> STATE;
int D[2<<LEN];
STATE state;

int dfs()
{
    int id = state.to_ulong();
    int& ans = D[id];
    if(ans >= 0) return ans;
    ans = state.count();
    
    for(int B = 1; B < LEN - 1; B++)
    {
        if(state[B] && (state[B-1] != state[B+1]))
        {
            state.flip(B-1);
            state.reset(B);
            state.flip(B+1);
            
            ans = min(ans, dfs());
            
            // 恢复
            state.flip(B-1);
            state.set(B);
            state.flip(B+1);
        }
    }
    
    return ans;
}

int main()
{
    state = 0;
    int n; 
    char buf[16];
    memset(D, -1, sizeof(D));
    scanf("%d\n", &n);
    while(n--)
    {
        gets(buf);
        for(int i = 0; i < LEN; i++)
            state.set(i, buf[i] == 'o' ? 1 : 0);
        
        printf("%d\n", dfs());
    }
    
    return 0;
}
