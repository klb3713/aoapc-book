// LA3641 Leonardo's Notebook
// Rujia Liu
#include<cstdio>
#include<cstring>
int main() {
  char B[30];
  int vis[30], cnt[30], T;
  scanf("%d", &T);
  while(T--) {
    scanf("%s", B);
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < 26; i++)
      if(!vis[i]) { // 找一个从i开始的循环
        int j = i, n = 0;
        do {
          vis[j] = 1; // 标记j为“已访问”
          j = B[j] - 'A';
          n++;
        } while(j != i);
        cnt[n]++;
      }
    int ok = 1;
    for(int i = 2; i <= 26; i++)
      if(i%2 == 0 && cnt[i]%2 == 1) ok = 0;
    if(ok) printf("Yes\n"); else printf("No\n");
  }
  return 0;
}
