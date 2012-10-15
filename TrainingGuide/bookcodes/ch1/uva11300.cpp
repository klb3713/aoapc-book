// UVa11300 Spreading The Wealth
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
long long A[maxn], C[maxn], tot, M;
int main() {
  int n;
  while(scanf("%d", &n) == 1) { // 输入数据大，scanf比cin快 
    tot = 0;
    for(int i = 1; i <= n; i++) { scanf("%lld", &A[i]); tot += A[i]; } // 用%lld输入long long
    M = tot / n;
    C[0] = 0; 
    for(int i = 1; i < n; i++) C[i] = C[i-1] + A[i] - M; // 递推C数组
    sort(C, C+n);
    long long x1 = C[n/2], ans = 0; // 计算x1
    for(int i = 0; i < n; i++) ans += abs(x1 - C[i]); 
    // 把x1代入，计算转手的总金币数
    printf("%lld\n", ans);
  }
  return 0;
}
