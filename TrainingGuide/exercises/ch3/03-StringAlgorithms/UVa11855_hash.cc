// UVa11855 Buzzwords
// 11645770	11855	Buzzwords	Accepted	C++	0.144	2013-04-21 15:40:21
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
typedef unsigned long long uint64;
const int maxn = 1024, x = 123;
uint64 H[maxn], xp[maxn];
int n;
char s[maxn], line[maxn];

bool dup(int L)
{
    int c = 1, maxI = n-L+1;
    vector<uint64> hash;
    for(int i = 0; i < maxI; i++) {
        int t = H[i] - H[i+L]*xp[L];
        hash.push_back(t);
    }
    
    sort(hash.begin(), hash.end());
    
    vector<int> cnt;
    for(int i = 1; i < hash.size(); i++){
        if(hash[i] != hash[i-1])  {
            cnt.push_back(c);
            c = 1; 
        }
        else c++;
    }
    cnt.push_back(c);
    sort(cnt.begin(), cnt.end(), greater<int>());
    
    int ans = cnt[0];
    if(ans > 1) printf("%d\n", ans);
    return ans > 1;
}

void solve()
{
    H[n] = 0;
    for(int i = n-1; i >= 0; i--) H[i] = H[i+1]*x + (s[i] - 'A');
    xp[0] = 1;
    for(int i = 1; i <= n; i++) xp[i] = xp[i-1]*x;
    
    for(int L = 1; L <= n; L++)
        if(!dup(L)) break;
    puts("");
}

int main()
{
    while(true)
    {
        if(!gets(line)) break;
        int len = strlen(line);
        if(len < 1) break;
        n = 0;
        for(int i = 0; i < len; i++)
            if(isupper(line[i])) s[n++] = line[i];
        s[n] = 0;
        
        if(n < 1) puts("0\n");
        else solve();
    }
    
    return 0;
}
