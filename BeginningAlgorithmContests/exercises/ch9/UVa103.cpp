// UVa103 Stacking Boxes
// Rujia Liu
// 题意：输入k个n维盒子(k<=30, n<=10)，找一个最长嵌套序列。
// 算法：DAG上的最长路。首先把盒子的各个维排序，这样判断起来比较简单
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxk = 30 + 5;
const int maxn = 10 + 5;
int n, k, box[maxk][maxn], d[maxk], next[maxk];

int dp(int i) {
  int& ans = d[i];
  if(ans > 0) return ans;
  ans = 1;
  next[i] = -1;
  for(int j = 0; j < k; j++) {
    bool bigger = true;
    for(int dim = 0; dim < n; dim++)
      if(box[j][dim] <= box[i][dim]) { bigger = false; break; }
    if(bigger && dp(j) + 1 > ans) {
      ans = dp(j) + 1;
      next[i] = j;
    }
  }
  return ans;
}

int main() {
  while(scanf("%d%d", &k, &n) == 2) {
    for(int i = 0; i < k; i++) {
      for(int j = 0; j < n; j++) scanf("%d", &box[i][j]);
      sort(box[i], box[i]+n);
    }
    memset(d, 0, sizeof(d));
    int ans = 0, first = -1;
    for(int i = 0; i < k; i++)
      if(dp(i) > ans) { ans = dp(i); first = i; }

    printf("%d\n%d", ans, first+1);
    for(int idx = next[first]; idx >= 0; idx = next[idx])
      printf(" %d", idx+1);
    printf("\n");
  }
  return 0;
}
