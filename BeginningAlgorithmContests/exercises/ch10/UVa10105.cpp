// UVa10105 Polynomial coefficients
// Rujia Liu
// 题意：输入正整数n, k，以及k个非负整数n1, n2, ..., nk, 输出(x1+x2+...+xk)^n中x1^n1*x2^n2*...*xk^nk的系数
// 算法：从n个因子中选n1个x1，再选n2个x2，再选n3个x3...，因此所求为C(n,n1)*C(n-n1,n2)*...
#include<iostream>
using namespace std;

const int maxn = 12;
long long C[maxn+1][maxn+1];

// 递推出所有组合数
void init() {
  for(int i = 0; i <= maxn; i++) {
    C[i][0] = 1;
    for(int j = 1; j <= i; j++)
      C[i][j] = C[i-1][j] + C[i-1][j-1]; // 注意i=0时不会执行这条语句
  }
}

int main() {
  init();
  int n, k, ni;
  while(cin >> n >> k && n) {
    long long ans = 1;
    for(int i = 0; i < k; i++) {
      cin >> ni;
      ans *= C[n][ni];
      n -= ni;
    }
    cout << ans << "\n";
  }
  return 0;
}
