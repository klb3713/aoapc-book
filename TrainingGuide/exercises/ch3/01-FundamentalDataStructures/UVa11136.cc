// UVa11136 Hoax or what
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <set>

using namespace std;

int n;
void solve()
{
    long long ans = 0;
    multiset<int> buf;
    for(int i = 0; i < n; i++)
    {
        int k, bill, max, min;
        scanf("%d", &k);
        
        for(int j = 0; j < k; j++)
        {
            scanf("%d", &bill);
            buf.insert(bill);
        }        
        
        max = *(buf.rbegin());
        min = *(buf.begin());
        ans += max - min;
        buf.erase(buf.find(max));
        buf.erase(buf.find(min));
    }
    
    printf("%lld\n", ans);
}

int main()
{
    while(true)
    {
        scanf("%d", &n);
        if(n == 0) break;
        solve();
    }
    
    return 0;
}
