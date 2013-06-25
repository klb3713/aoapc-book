// UVa10026 Shoemaker's Problem
// Rujia Liu
// 题意：鞋匠接收了许多订单，有些鞋子有一定的修理期限，超过了这个期限就会罚款，让你求出最少赔款的方案，如果有多个相同的，请按输入的顺序从小到大输出。
// 算法：按照fine/time从大到小修
#include<cstdio>
#include<algorithm>
using namespace std;

struct Job {
  int idx, time, cost;
  Job(int idx=0, int time=0, int cost=0):idx(idx),time(time),cost(cost){}
  bool operator < (const Job& rhs) const {
    return rhs.cost*time < rhs.time*cost || (rhs.cost*time == rhs.time*cost && idx < rhs.idx);
  }
};

const int maxn = 1000 + 5;
Job jobs[maxn];

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
   int n, time, cost;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &time, &cost); 
      jobs[i] = Job(i+1, time, cost);
    }
    sort(jobs, jobs+n);
    for(int i = 0; i < n-1; i++) printf("%d ", jobs[i].idx);
    printf("%d\n", jobs[n-1].idx);
    if(T) printf("\n");
  }
  return 0;
}
