// UVa11995 I Can Guess the Data Structure!	
// Rujia Liu
#include<cstdio>
#include<queue>
#include<stack>
#include<cstdlib>
using namespace std;

const int maxn = 1000 + 10;
int n, t[maxn], v[maxn];

int check_stack() {
  stack<int> s;
  for(int i = 0; i < n; i++) {
    if(t[i] == 2) {
      if(s.empty()) return 0;
      int x = s.top(); s.pop();
      if(x != v[i]) return 0;
    }
    else s.push(v[i]);
  }
  return 1;
}

int check_queue() {
  queue<int> s;
  for(int i = 0; i < n; i++) {
    if(t[i] == 2) {
      if(s.empty()) return 0;
      int x = s.front(); s.pop();
      if(x != v[i]) return 0;
    }
    else s.push(v[i]);
  }
  return 1;
}

int check_pq() {
  priority_queue<int> s;
  for(int i = 0; i < n; i++) {
    if(t[i] == 2) {
      if(s.empty()) return 0;
      int x = s.top(); s.pop();
      if(x != v[i]) return 0;
    }
    else s.push(v[i]);
  }
  return 1;
}

int main() {
  while(scanf("%d", &n) == 1) {
    for(int i = 0; i < n; i++) scanf("%d%d", &t[i], &v[i]);
    int s = check_stack();
    int q = check_queue();
    int pq = check_pq();
    if(!s && !q && !pq) printf("impossible\n");
    else if(s && !q && !pq) printf("stack\n");
    else if(!s && q && !pq) printf("queue\n");
    else if(!s && !q && pq) printf("priority queue\n");
    else printf("not sure\n");
  }
  return 0;
}
