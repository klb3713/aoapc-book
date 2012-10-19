// LA3510 Pixel Shuffle （限于篇幅，书上无此代码）
// Rujia Liu
#include<cctype>
#include<cstring>

int gcd(int a, int b) {
  if(!b) return a;
  else return gcd(b, a%b);
}

int lcm(int a, int b) {
  return a / gcd(a,b) * b;
}

#define ID(i, j) ((i)*n+(j))

// 求位置(i,j)经过操作op进行正向变换后的新位置
int newpos(int n, int i, int j, const char* op) {
  if(op[0] == 'r') // rot
    return ID(n-1-j, i);
  if(op[0] == 's') // sym
    return ID(i, n-1-j);
  if(op[0] == 'b' && op[1] == 'h') // bhsym
    return i < n/2 ? ID(i, j) : ID(i, n-1-j);
  if(op[0] == 'b' && op[1] == 'v') // bvsym
    return i < n/2 ? ID(i, j) : ID(n/2+n-i-1, j);
  if(op[0] == 'd') // div
    return i % 2 == 0 ? ID(i/2, j) : ID(n/2+i/2, j);
  if(op[0] == 'm') { // mix
    int k = i/2;
    if(j < n/2)
      return i % 2 == 0 ? ID(2*k, 2*j) : ID(2*k, 2*j+1);
    else
      return i % 2 == 0 ? ID(2*k+1, 2*(j-n/2)) : ID(2*k+1, 2*(j-n/2)+1);
  }
  return ID(i, j); // id
}

const int maxn = 1024;

// 变换一张n*n图片
int orig[maxn*maxn];
void apply(int* image, int n, const char* op) {
  bool inv = op[strlen(op)-1] == '-';
  for(int i = 0; i < n*n; i++) orig[i] = image[i];  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
      int p = ID(i, j), p2 = newpos(n, i, j, op);
      if(!inv) image[p2] = orig[p];
      else image[p] = orig[p2];
    }
}

// 已知n元素置换p，求最小的m使得p^m=I
int vis[maxn*maxn];
int solve(int* p, int n) {
  memset(vis, 0, sizeof(vis));
  int ans = 1;
  for(int i = 0; i < n; i++)
    if(!vis[i]) {
      int j = i, len = 0; // len是循环节
      do {
        vis[j] = 1;
        j = p[j];
        len++;
      } while(j != i);
      ans = lcm(ans, len);
    }
  return ans;
}

#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int cur[maxn*maxn];
int main() {
  int T, n;
  cin >> T >> n;
  while(T--) {
    int n2;
    for(int i = 0; i < n*n; i++) cur[i] = i;
    vector<string> ops;
    for(int i = 0; ; i++) {
      string op;
      if(!(cin >> op)) break;
      if(isdigit(op[0])) { sscanf(op.c_str(), "%d", &n2); break; }
      ops.push_back(op);
    }
    for(int i = ops.size()-1; i >= 0; i--) // 注意，操作是逆序执行的
      apply(cur, n, ops[i].c_str());
    cout << solve(cur, n*n) << "\n";
    if(T) cout << "\n";
    n = n2;
  }
  return 0;
}
