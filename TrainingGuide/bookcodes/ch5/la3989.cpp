// LA3989 Ladies' Choice
// Rujia Liu
#include<cstdio>
#include<queue>
using namespace std;

const int maxn = 1000 + 10;
int pref[maxn][maxn], order[maxn][maxn], next[maxn], future_husband[maxn], future_wife[maxn];
queue<int> q; // 未订婚的男士队列

void engage(int man, int woman) {
  int m = future_husband[woman];
  if(m) {
    future_wife[m] = 0; // 抛弃现任未婚夫（如果有的话）
    q.push(m); // 加入未订婚男士队列
  }
  future_wife[man] = woman;
  future_husband[woman] = man;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++)
        scanf("%d", &pref[i][j]); // 编号为i的男士第j喜欢的人
      next[i] = 1; // 接下来应向排名为1的女士求婚
      future_wife[i] = 0; // 没有未婚妻
      q.push(i);
    }

    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        int x;
        scanf("%d", &x);
        order[i][x] = j; // 在编号为i的女士心目中，编号为x的男士的排名
      }
      future_husband[i] = 0; // 没有未婚夫
    }

    while(!q.empty()) {
      int man = q.front(); q.pop();
      int woman = pref[man][next[man]++];
      if(!future_husband[woman]) engage(man, woman); // woman没有未婚夫，直接订婚
      else if(order[woman][man] < order[woman][future_husband[woman]]) engage(man, woman); // 换未婚夫
      else q.push(man); // 下次再来
    }
    while(!q.empty()) q.pop();

    for(int i = 1; i <= n; i++) printf("%d\n", future_wife[i]);
    if(T) printf("\n");
  }
  return 0;
}
