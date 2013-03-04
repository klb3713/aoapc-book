// UVa11137 Ingenuous Cubrency
// Rujia Liu
#include<cstring>
#include<iostream>
using namespace std;

long long d[30][10010];
int main() {
  memset(d, 0, sizeof(d));
  d[0][0] = 1;
  for(int i = 1; i <= 25; i++)
    for(int j = 0; j <= 10000; j++) {
      d[i][j] = d[i-1][j];
      if(j>=i*i*i) d[i][j] += d[i][j-i*i*i];
    }

  int n;
  while(cin >> n) {
    cout << d[25][n] << endl;    
  }
  return 0;
}
