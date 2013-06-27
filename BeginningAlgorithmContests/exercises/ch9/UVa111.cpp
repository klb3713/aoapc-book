// UVa111 History Grading
// Rujia Liu
// 题意：历史考试中有一道年代排序题，假定正确的事件顺序为A，考生写的是B，则二者的LCS为得分。输入正确答案和考生答案中每个事件的序号，求考生得分。
// 算法：注意输入的是每个事件的序号，而LCS是针对的按时间顺序的事件排列
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20 + 5;
int n, A[maxn], B[maxn], d[maxn][maxn];

int LCS() {
  memset(d, 0, sizeof(d));
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++) {
      if(A[i] == B[j]) d[i][j] = d[i-1][j-1] + 1;
      else d[i][j] = max(d[i][j-1], d[i-1][j]);
    }
  return d[n][n];
}

bool read() {
  int x;
  for(int i = 0; i < n; i++) {
    if(!(cin >> x)) return false;
    B[x] = i;
  }
  return true;
}

int main() {
  cin >> n;
  for(int i = 0; i < n; i++) { int x; cin >> x; A[x] = i; }
  while(read()) {
    cout << LCS() << "\n";
  }
  return 0;
}
