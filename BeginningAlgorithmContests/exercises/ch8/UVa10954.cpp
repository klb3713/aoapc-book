// UVa10954 Add All
// Rujia Liu
// 题意：有n个数的集合S，每次可以从S中删除两个数，然后把它们的和放回集合，直到剩一个数。每次操作的开销等于删除的两个数之和。求最小总开销。
// 算法：Huffman编码
#include<cstdio>
#include<queue>
using namespace std;

int main() {
  int n, x;
  while(scanf("%d", &n) == 1 && n) {
    priority_queue<int, vector<int>, greater<int> > q;
    for(int i = 0; i < n; i++) { scanf("%d", &x); q.push(x); }
    int ans = 0;
    for(int i = 0; i < n-1; i++) {
      int a = q.top(); q.pop();
      int b = q.top(); q.pop();
      ans += a+b;
      q.push(a+b);
    }
    printf("%d\n", ans);
  }
  return 0;
}
