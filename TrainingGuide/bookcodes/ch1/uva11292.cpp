// UVa11292 The Dragon of Loowater
// Rujia Liu
#include<cstdio>
#include<algorithm>       // 因为用到了sort
using namespace std;

const int maxn = 20000 + 5;
int A[maxn], B[maxn];
int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2 && n && m) {
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    for(int i = 0; i < m; i++) scanf("%d", &B[i]);
    sort(A, A+n);
    sort(B, B+m);
    int cur = 0;         // 当前需要砍掉的头的编号
    int cost = 0;        // 当前总费用
    for(int i = 0; i < m; i++)
      if(B[i] >= A[cur]) {
        cost += B[i];           // 雇佣该骑士
        if(++cur == n) break;   // 如果头已经砍完，及时退出循环
      }
    if(cur < n) printf("Loowater is doomed!\n");
    else printf("%d\n", cost);
  }
  return 0;
}
