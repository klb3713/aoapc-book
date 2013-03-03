// Uva10954	Add All
// 陈锋
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;
const int MAXN = 5120;
int main()
{
    multiset<int> integers;
    while(true)
    {
        int N;
        scanf("%d", &N);
        if(N == 0) break;

        integers.clear();
        for(int i = 0; i < N; i++)
        {
            int num;
            scanf("%d", &num);
            integers.insert(num);
        }        
        
        long long cost = 0;
        while(integers.size() > 1)
        {
            // 每次都取最前面的两个最小的整数相加来计算cost
            int sum = *(integers.begin());
            integers.erase(integers.begin());
            sum += *(integers.begin());
            integers.erase(integers.begin());
            
            integers.insert(sum); // 之后把作为新的整数插入整数列表
            
            cost += sum;
        }
        
        printf("%lld\n", cost);
    }
    return 0;
}
