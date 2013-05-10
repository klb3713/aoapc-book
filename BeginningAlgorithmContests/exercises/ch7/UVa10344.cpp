// UVa10344 23 Out of 5
// Rujia Liu
// 题意：输入5个整数，按照某种顺序排列后依次进行+, -或者*，使得最终结果为23。判断是否有解
// 算法：回溯
#include<cstdio>
#include<cstring>
int a[5], vis[5];

// d为当前层数，v为当前数值
bool dfs(int d, int v) {
  if(d == 5) return v == 23;
  for(int i = 0; i < 5; i++) if(!vis[i]) {
    vis[i] = 1;
    if(d == 0) { if(dfs(d+1, a[i])) return true; }
    else {      
      if(dfs(d+1, v + a[i])) return true;
      if(dfs(d+1, v - a[i])) return true;
      if(dfs(d+1, v * a[i])) return true;
    }
    vis[i] = 0;
  }
  return false;
}

int main() {
  for(;;) {
    bool over = true;
    for(int i = 0; i < 5; i++) { scanf("%d", &a[i]); if(a[i] != 0) over = false; }
    if(over) break;
    memset(vis, 0, sizeof(vis));
    if(dfs(0, 0)) printf("Possible\n"); else printf("Impossible\n");
  }
  return 0;
}
