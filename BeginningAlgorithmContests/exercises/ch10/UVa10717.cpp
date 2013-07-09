// UVa10717 Mint
// Rujia Liu
// 题意：有一种新型桌子，每个桌子腿都是由一种不同的硬币摞起来组成的。四个桌子腿必须等高。
// 输入4<=n<=50种硬币的高度，以及t个理想的桌子腿高度，对于每个理想高度h，输出在可能达到的桌子腿高度中，<=h的最大高度和>=h的最小高度。
// 算法：枚举用哪四种硬币，求最小公倍数（这一步可以预处理，免得重复计算），然后更新所求结果
#include<iostream>
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
using namespace std;

const int maxn = 50 + 5;
int coin[maxn], minh[maxn][maxn][maxn][maxn]; // 预处理结果

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
  return a / gcd(a, b) * b;
}

int ans1, ans2;
void update_ans(int h, int h0) {
  if(h % h0 == 0) { ans1 = ans2 = h; }
  else {
    int d = h / h0;
    if(ans1 < 0 || d * h0 > ans1) ans1 = d * h0;
    if(ans2 < 0 || (d+1) * h0 < ans2) ans2 = (d+1) * h0;
  }
}

int main() {
  int n, t, h;
  while(cin >> n >> t && n) {
    FOR(i,0,n) cin >> coin[i];
    FOR(a,0,n) FOR(b,a+1,n) FOR(c,b+1,n) FOR(d,c+1,n) {
      minh[a][b][c][d] = lcm(coin[a], lcm(coin[b], lcm(coin[c], coin[d])));
    }
    while(t--) {
      cin >> h;
      ans1 = -1, ans2 = -1;
      FOR(a,0,n) FOR(b,a+1,n) FOR(c,b+1,n) FOR(d,c+1,n)
        update_ans(h, minh[a][b][c][d]);
      cout << ans1 << " " << ans2 << "\n";
    }
  }
  return 0;
}
