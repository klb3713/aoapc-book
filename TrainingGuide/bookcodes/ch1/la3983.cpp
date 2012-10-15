// LA3983 Robotruck
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;

int x[maxn], y[maxn];
int total_dist[maxn], total_weight[maxn], dist2origin[maxn];
int q[maxn], d[maxn];

int func(int i) {
  return d[i] - total_dist[i+1] + dist2origin[i+1];
}

main() {
  int T, c, n, w, front, rear;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &c, &n);
    total_dist[0] = total_weight[0] = x[0] = y[0] = 0;
    for(int i = 1; i <= n; i++) {
      scanf("%d%d%d", &x[i], &y[i], &w);
      dist2origin[i] = abs(x[i]) + abs(y[i]);
      total_dist[i] = total_dist[i-1] + abs(x[i]-x[i-1]) + abs(y[i]-y[i-1]);
      total_weight[i] = total_weight[i-1] + w;
    }
    front = rear = 1;
    for (int i = 1; i <= n; i++) {
      while (front <= rear && total_weight[i] - total_weight[q[front]] > c) front++;
      d[i] = func(q[front]) + total_dist[i] + dist2origin[i];
      while (front <= rear && func(i) <= func(q[rear])) rear--;
      q[++rear] = i;
    }
    printf("%d\n", d[n]);
    if(T > 0) printf("\n");
  }
  return 0;
}
