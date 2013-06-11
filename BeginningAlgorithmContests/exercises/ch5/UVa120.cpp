// UVa120 Stacks of Flapjacks
// Rujia Liu
// 题意：输入n个不同正整数，每次可以选一个数k，把从第一个数到右数第k个数翻转一下，最后变成升序
// 举例：5 1 2 3 4经过操作1变成4 3 2 1 5，再经过操作2变成1 2 3 4 5，结束。
// 算法：按照从大到小的顺序依次把各个数弄到正确的位置，具体方法是把它转到最左边，再转到正确位置
#include<cstdio>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;
int n, a[maxn];

// 翻转a[0..p]
void flip(int p) {
  for(int i = 0; i < p-i; i++)
    swap(a[i], a[p-i]);
  printf("%d ", n-p);
}

int main() {
  string s;
  while(getline(cin, s)) {
    cout << s << "\n";
    stringstream ss(s);
    n = 0;
    while(ss >> a[n]) n++;
    for(int i = n-1; i > 0; i--) {
      int p = max_element(a, a+i+1) - a; // 元素a[0..i]中的最大元素
      if(p == i) continue;
      if(p > 0) flip(p); // flip(0)没啥意思，是不？
      flip(i);
    }
    printf("0\n");
  }
  return 0;
}
