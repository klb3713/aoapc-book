// UVa529 Addition Chains
// 陈锋
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXLEVEL = 32;

int sequence[MAXLEVEL];
int lower_bounds[MAXLEVEL];

bool dfs(int *seq, int cur, int len, int target)
{
    if(cur == len)
    {
        if(seq[cur-1] == target) return true;
    }
    else
    {
        int next, last = seq[cur-1], lower = lower_bounds[cur];
        for(next = min(2*last, target); next >= lower; next--)
        {
            bool found = false;
            for(int i = cur - 1; i >= 0; i--)
            {
                found = binary_search(seq, seq + cur, next - seq[cur-1]);
                if(found) break;
            }
            
            if(found)
            {
                seq[cur] = next;
                if(dfs(seq, cur + 1, len, target)) return true;
            }
        }
    }
    return false;
}

int main()
{
    int n;
    sequence[0] = 1;
    sequence[1] = 2;
    lower_bounds[0] = 1;
    lower_bounds[1] = 2;
    lower_bounds[3] = 3;
    while(true)
    {
        scanf("%d", &n);
        if(n == 0) 
            break;
        else if(n == 1)
            puts("1");
        else if(n == 2)
            puts("1 2");
        else
        {
            int len = 0, i = n;
            while(i)
            {
                len++;
                i >>= 1;
            } // 每一个n的加法链都有个最低级别
            
            for(; len < MAXLEVEL; len++)
            {
                i = len - 1;
                lower_bounds[i] = n;
                while(i-- > 2)
                    lower_bounds[i] = lower_bounds[i+1] / 2 + lower_bounds[i+1] % 2;
                // 每个级别都有一个最小值，小于这个最小值的分支不可能搜索到最短链
                if(dfs(sequence, 2, len, n)) break;
            }
            
            for(len = 0; len < n; len++)
            {                
                if(sequence[len] == n) break;
                printf("%d ", sequence[len]);                
            }
            printf("%d\n", n);
        }
    }
    return 0;
}
