// UVa10910 Marks Distribution
// Rujia Liu
// 题意：某人参加了N门考试，总分为T，最低分为P。求有多少种可能的分数。N,T,P<=70，输出在32位带符号整数范围内
// 算法：答案就是x1+x2+...+xN=T-(P-1)N的正整数解。用隔板法，一共有T-(P-1)N-1位置，放N-1个隔板
// 注意虽然结果不会溢出，但是计算组合数的过程中可能会溢出
#include<iostream>
using namespace std;

long long C(int n, int m) {
  double ans = 1;
  if(n-m > m) m = n-m;
  for(int i = m+1; i <= n; i++) ans *= i;
  for(int i = 1; i <= n-m; i++) ans /= i;
  return ans + 0.5;
}

long long F(int N, int T, int P) {
  return C(T-(P-1)*N-1, N-1);
}

int main() {
  int N, T, P, kases;
  cin >> kases;
  while(kases--) {
    cin >> N >> T >> P;
    cout << F(N, T, P) << "\n";
  }
  return 0;
}
