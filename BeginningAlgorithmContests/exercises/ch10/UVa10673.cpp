// UVa10673 Play with Floor and Ceil
// Rujia Liu
// 题意：输入两个正整数x, k，找两个整数p, q使得x = p*floor(x/k) + q*ceil(x/k)。
// 算法：如果x是k的倍数，则只要p+q=k即可，否则floor(x/k)+1=ceil(x/k)，因此二者互素，用扩展欧几里得算法即可
#include<iostream>
using namespace std;

typedef long long LL;

// 即使a, b在int范围内，x和y有可能超出int范围
void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
  if(!b){ d = a; x = 1; y = 0; }
  else{ gcd(b, a%b, d, y, x); y -= x*(a/b); }
}

int main() {
  int T, x, k;
  cin >> T;
  while(cin >> x >> k) {
    if(x % k == 0) cout << 0 << " " << k << "\n";
    else {
      int a = x/k, b = a+1;
      LL d, p, q;
      gcd(a, b, d, p, q);
      cout << p * x << " " << q * x << "\n";
    }
  }
  return 0;
}
