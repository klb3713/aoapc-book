// UVa10131 Is Bigger Smarter?
// Rujia Liu
// 题意：输入n只大象的体重W和智力S，求一个最长的大象序列使得体重严格递增且智力严格递减
// 算法：类似于LIS，先按照体重从小到大排序，然后动态规划
// d[i]为以i结尾的最长大象序列，则d[i] = max{0, d[j] | j < i, W[j] < W[i], S[j] > S[i]} + 1
#include<cstdio>
#include<algorithm>
using namespace std;

struct Elephant {
  int W, S, idx;
  bool operator < (const Elephant& rhs) const {
    return W < rhs.W;
  }
};

const int maxn = 1000 + 5;
int d[maxn], p[maxn];
Elephant elephants[maxn];

void print(int i) {
  if(i < 0) return;
  print(p[i]);
  printf("%d\n", elephants[i].idx);
}

int main() {
  int n = 0;
  while(scanf("%d%d", &elephants[n].W, &elephants[n].S) == 2) {
    elephants[n].idx = n+1;
    n++;
  }
  sort(elephants, elephants+n);

  int ans = 0, last = -1;
  for(int i = 0; i < n; i++) {
    d[i] = 0;
    p[i] = -1;
    for(int j = 0; j < i; j++)
      if(elephants[j].W < elephants[i].W && elephants[j].S > elephants[i].S) {
        if(d[j] > d[i]) { d[i] = d[j]; p[i] = j; }
      }
    d[i]++;
    if(d[i] > ans) {
      ans = d[i];
      last = i;
    }
  }
  printf("%d\n", ans);
  print(last);
  return 0;
}
