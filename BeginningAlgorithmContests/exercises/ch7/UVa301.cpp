// UVa301 Transportation
// Rujia Liu
// 题意：有一辆能容纳n个人的火车从站0出发，依次停靠站1, 2, ..., m。
// 有t个形如(from, to, num)的订单，表示有num个人从from站到to站，票价为(to-from)*num。接受其中一些订单，使得收益（订单总票价）最大
// 算法：回溯。注意本题有一个简单有效的最优性剪枝

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxm = 10;
const int maxt = 25;
int n, m, t, ans, from[maxt], to[maxt], num[maxt], cnt[maxm];

void dfs(int d, int tot) {
  // 最优性剪枝：如果剩下所有订单都接受还是无法超过当前找到的最优解，则剪枝
  int extra = 0;
  for(int i = d; i < t; i++) extra += num[i] * (to[i] - from[i]);
  if(tot + extra <= ans) return;

  ans = max(ans, tot);
  if(d == t) return;
  dfs(d+1, tot);
  bool ok = true;
  for(int i = from[d]; i < to[d]; i++) {
    cnt[i] += num[d];
    if(cnt[i] > n) ok = false; // 坐不下
  }
  if(ok) dfs(d+1, tot + num[d] * (to[d] - from[d]));
  for(int i = from[d]; i < to[d]; i++) {
    cnt[i] -= num[d];
  }
}

int main() {
  while(scanf("%d%d%d", &n, &m, &t) == 3 && n) {
    for(int i = 0; i < t; i++) scanf("%d%d%d", &from[i], &to[i], &num[i]);
    memset(cnt, 0, sizeof(cnt));
    ans = 0;
    dfs(0, 0);
    printf("%d\n", ans);
  }
  return 0;
}
