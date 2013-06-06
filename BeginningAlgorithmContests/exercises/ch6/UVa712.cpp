// UVa712 S-Trees
// Rujia Liu
// 题意：给一棵满二叉树，每一层代表一个01变量，取0时往左走，取1时往右走。给出所有叶子的值，以及一些查询（即每个变量的值），求最后到达的叶子的值
// 算法：结点从上到下编号为1, 2, 3, ...则左走就是乘以2，右走是乘以2加1。第一个叶子的编号是2^n
#include<iostream>
#include<string>
using namespace std;

const int maxn = 10;
int n, v[maxn];
string leaves;

int solve(const string& q) {
  int u = 1;
  for(int i = 0; i < n; i++) {
    if(q[v[i]] == '0') u *= 2; else u = u*2+1;
  }
  return leaves[u-(1<<n)] - '0';
}

int main() {
  int kase = 0;
  while(cin >> n && n) {
    string s;
    cout << "S-Tree #" << ++kase << ":\n";
    for(int i = 0; i < n; i++) { cin >> s; v[i] = s[1] - '1'; }
    int m;
    cin >> leaves >> m;
    while(m--) {
      string q;
      cin >> q;
      cout << solve(q);
    }
    cout << "\n\n";
  }
  return 0;
}
