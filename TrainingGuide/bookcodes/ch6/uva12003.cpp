// UVa12003 Array Transformer
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 300000 + 10;
const int SIZE = 4096;

int n, m, u, A[maxn], block[maxn/SIZE+1][SIZE];

void init() {
  scanf("%d%d%d", &n, &m, &u);
  int b = 0, j = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
    block[b][j] = A[i];
    if(++j == SIZE) { b++; j = 0; }
  }
  for(int i = 0; i < b; i++) sort(block[i], block[i]+SIZE);
  if(j) sort(block[b], block[b]+j);
}

int query(int L, int R, int v) {
  int lb = L/SIZE, rb = R/SIZE; // L和R所在块编号
  int k = 0;
  if(lb == rb) {
    for(int i = L; i <= R; i++) if(A[i] < v) k++;
  } else {
    for(int i = L; i < (lb+1)*SIZE; i++) if(A[i] < v) k++; // 第一块
    for(int i = rb*SIZE; i <= R; i++) if(A[i] < v) k++; // 最后一块
    for(int b = lb+1; b < rb; b++) // 中间的完整块
      k += lower_bound(block[b], block[b]+SIZE, v) - block[b];
  }
  return k;
}

void change(int p, int x) {
  if(A[p] == x) return;
  int old = A[p], pos = 0, *B = &block[p/SIZE][0]; // B就是p所在的块
  A[p] = x;

  while(B[pos] < old) pos++; B[pos] = x; // 找到x在块中的位置
  if(x > old) // x太大，往后交换
    while(pos < SIZE-1 && B[pos] > B[pos+1]) { swap(B[pos+1], B[pos]); pos++; }
  else // 往前交换
    while(pos > 0 && B[pos] < B[pos-1]) { swap(B[pos-1], B[pos]); pos--; }
}

int main() {
  init();
  while(m--) {
    int L, R, v, p;
    scanf("%d%d%d%d", &L, &R, &v, &p); L--; R--; p--;
    int k = query(L, R, v);
    change(p, (long long)u * k / (R-L+1));
  }
  for(int i = 0; i < n; i++) printf("%d\n", A[i]);
  return 0;
}
