// UVa11137 Ingenuous Cubrency
// Rujia Liu
// 复杂度较高的方法
#include<cstring>
#include<iostream>
using namespace std;

long long d[30][10010];
int main() {
  memset(d, 0, sizeof(d));
  d[0][0] = 1;
  for(int i = 1; i <= 25; i++)
    for(int j = 0; j <= 10000; j++)
      for(int a = 0; j+a*i*i*i<=10000; a++)
        d[i][j+a*i*i*i] += d[i-1][j];

  int n;
  while(cin >> n) {
    cout << d[25][n] << endl;    
  }
  return 0;
}
