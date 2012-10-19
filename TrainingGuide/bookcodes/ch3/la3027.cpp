// LA3027 Corporative Network
// Rujia Liu
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int maxn = 20000 + 10;
int pa[maxn], d[maxn];

int findset( int x ) {
  if (pa[x] != x) {
    int root = findset( pa[x] );
    d[x] += d[pa[x]];
    return pa[x] = root; 
  } else return x;
}

int main() {
  int T;
  cin >> T;
  while(T--) {
    int n, u, v;
    string cmd;
    cin >> n;
    for(int i = 1; i <= n; i++) { pa[i] = i; d[i] = 0; }
    while(cin >> cmd && cmd[0] != 'O') {
      if(cmd[0] == 'E') { cin >> u; findset(u); cout << d[u] << endl; }
      if(cmd[0] == 'I') { cin >> u >> v; pa[u] = v; d[u] = abs(u-v) % 1000; }
    }
  }
  return 0;
}