#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAXN = 256;
const int root = 1;
int cnt, vis[MAXN], val[MAXN], left[MAXN], right[MAXN];

int newnode() { int u = ++cnt; left[u] = right[u] = vis[u] = 0; return u; }
void newtree() { left[root] = right[root] = vis[root] = 0; cnt = root; }

int failed;
void addnode(int v, char* s) {
  int n = strlen(s), u = root;
  for(int i = 0; i < n; i++)
    if(s[i] == 'L') {
      if(!left[u]) left[u] = newnode(); u = left[u];
    } else if(s[i] == 'R') {
      if(!right[u]) right[u] = newnode(); u = right[u];
    }
  if(vis[u]) failed = 1;
  val[u] = v;
  vis[u] = 1;
}

char s[MAXN + 10];
int read_input() {
  failed = 0;
  newtree();
  for(;;) {
    if(scanf("%s", s) != 1) return 0;
    if(!strcmp(s, "()")) break;
    int v;
    sscanf(&s[1], "%d", &v);
    addnode(v, strchr(s, ',')+1);
  }
  return 1;
}

int n, ans[MAXN];
int bfs() {
  int front = 0, rear = 1;
  int q[MAXN];
  q[0] = root;
  n = 0;
  while(front < rear) {
    int u = q[front++];
    if(!vis[u]) return 0;
    ans[n++] = val[u];
    if(left[u]) q[rear++] = left[u];
    if(right[u]) q[rear++] = right[u];
  }
  return 1;
}

int main() {
  while(read_input()) {
    if(!bfs()) failed = 1;
    if(failed) printf("not complete\n");
    else {
      for(int i = 0; i < n; i++) {
        if(i != 0) printf(" ");
        printf("%d", ans[i]);
      }
      printf("\n");
    }
  }
  return 0;
}
