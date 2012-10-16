// UVa11538 Chess Queen
// Rujia Liu
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
  unsigned long long n, m; // 最大可以保存2^64-1>1.8*10^19
  while(cin >> n >> m) {
    if(!n && !m) break;
    if(n > m) swap(n, m); // 这样就避免了对n<=m和n>m两种情况分类讨论
    cout << n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3 << endl;
  }
  return 0;
}
