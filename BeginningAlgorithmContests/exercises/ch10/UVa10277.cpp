// UVa10277 Boastin' Red Socks
// Rujia Liu
// 题意：你有a只红袜子和b-a只黑袜子，共b袜子。2<=b<=50000。随便拿两只出来都是红色的概率为p/q。输入p, q，求红黑袜子数量，或报告无解
// 算法：p/q=a*(a-1)/b*(b-1)，枚举b，则a*(a-1)=b*(b-1)*p/q，然后解出a即可。注意p=0的情况
#include<iostream>
#include<cmath>
using namespace std;

void solve(long long p, long long q) {
  if(p == 0) { cout << "0 2\n"; return; }
  for(long long b = 2; b <= 50000; b++) {
    long long x = b * (b-1) * p;
    if(x % q != 0) continue;
    x /= q;
    long long a = (long long)sqrt(x)+1;
    if(a*(a-1) == x) {
      cout << a << " " << b-a << "\n";
      return;
    }
  }
  cout << "impossible\n";
}

int main() {
  long long p, q;
  while(cin >> p >> q && q) // 注意p可以为0
    solve(p, q);
  return 0;
}

