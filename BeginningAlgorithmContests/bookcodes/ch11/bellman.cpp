#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int MAXN = 1000;
const int MAXM = 100000;

int n, m;
int first[MAXN], d[MAXN];
int u[MAXM], v[MAXM], w[MAXM], next[MAXM];

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) first[i] = -1;
  for(int e = 0; e < m; e++) {
    scanf("%d%d%d", &u[e], &v[e], &w[e]);
    next[e] = first[u[e]];
    first[u[e]] = e;
  }

  queue<int> q;
  bool inq[MAXN];
  for(int i = 0; i < n; i++) d[i] = (i==0 ? 0 : INF);
  memset(inq, 0, sizeof(inq));
  q.push(0);
  while(!q.empty()) {
    int x = q.front(); q.pop();
    inq[x] = false;
    for(int e = first[x]; e != -1; e = next[e]) if(d[v[e]] > d[x]+w[e]) {
      d[v[e]] = d[x] + w[e];
      if(!inq[v[e]]) {
        inq[v[e]] = true;
        q.push(v[e]);
      }
    }
  }

  for(int i = 0; i < n; i++)
    printf("%d\n", d[i]);
  return 0;
}
