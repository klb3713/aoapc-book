// UVa11401 Triangle Counting
// Rujia Liu
#include<iostream>
using namespace std;

long long f[1000010]; // int´æ²»ÏÂ
int main() {
  f[3] = 0;
  for(long long x = 4; x <= 1000000; x++)
    f[x] = f[x-1] + ((x-1)*(x-2)/2 - (x-1)/2)/2; // µÝÍÆ

  int n;
  while(cin >> n) {
    if(n < 3) break;
    cout << f[n] << endl;    
  }
  return 0;
}
