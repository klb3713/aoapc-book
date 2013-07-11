// UVa991 Safe Salutations
// Rujia Liu
// 题意：
// 算法：就是Catalan数（从C[0]开始），即：1, 1, 2, 5, 14, ... C[n+1] = C[n] * (4n+2)/(n+2)
#include<iostream>
using namespace std;

const int maxn = 10;

int C[maxn+1];

int main() {
  C[0] = 1;
  for(int i = 0; i < maxn; i++)
    C[i+1] = C[i] * (i*4+2) / (i+2);
  int n, kase = 0;
  while(cin >> n && n) {
    if(kase++ > 0) cout << "\n";
    cout << C[n] << "\n";
  }
  return 0;
}
