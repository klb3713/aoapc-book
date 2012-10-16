// LA3516 Exploring Pyramids
// Rujia Liu
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 300 + 10;
const int MOD = 1000000000;
typedef long long LL;

char S[maxn];
int d[maxn][maxn];

int dp(int i, int j) {
  if(i == j) return 1;
  if(S[i] != S[j]) return 0;
  int& ans = d[i][j];
  if(ans >= 0) return ans;
  ans = 0;
  for(int k = i+2; k <= j; k++) if(S[i] == S[k])
    ans = (ans + (LL)dp(i+1,k-1) * (LL)dp(k,j)) % MOD;
  return ans;
}

int main() {
  while(scanf("%s", S) == 1) {
    memset(d, -1, sizeof(d));
    printf("%d\n", dp(0, strlen(S)-1));
  }
  return 0;
}
