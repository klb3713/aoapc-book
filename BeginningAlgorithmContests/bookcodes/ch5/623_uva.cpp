#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int maxn = 1000;
const int maxd = 3000;

int f[maxd], len;
string fact[maxn + 1];

void store(int n) {
  for(int i = len-1; i >= 0; i--) fact[n] += (char)(f[i] + '0');
}

void init(int n) {
  int i, j;
  memset(f, 0, sizeof(f));
  len = 1;
  f[0] = 1;
  store(0);
  store(1);
  for(int i = 2; i <= n; i++) {
    int c = 0;
    for(int j = 0; ; j++) {
      int s = f[j] * i + c;
      f[j] = s % 10;
      c = s / 10;
      if(j >= len && c == 0) {
        len = j+1;
        while(len > 1 && f[len-1] == 0) len--;
        break;
      }
    }
    store(i);
  }
}

int main() {
  init(1000);
  int n;
  while(scanf("%d", &n) == 1) {
    printf("%d!\n%s\n", n, fact[n].c_str());
  }
  return 0;
}
