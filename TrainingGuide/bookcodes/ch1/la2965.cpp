// LA2965 Jurassic Remains
// Rujia Liu
#include<cstdio>
#include<map>
using namespace std;

const int maxn = 24;
map<int,int> table;

int bitcount(int x) { return x == 0 ? 0 : bitcount(x/2) + (x&1); }

int main() {
  int n, A[maxn];
  char s[1000];

  while(scanf("%d", &n) == 1 && n) {
    // 输入并计算每个字符串对应的位向量
    for(int i = 0; i < n; i++) {
      scanf("%s", s);
      A[i] = 0;
      for(int j = 0; s[j] != '\0'; j++) A[i] ^= (1<<(s[j]-'A'));
    }
    // 计算前n1个元素的所有子集的xor值
    // table[x]保存的是xor值为x的，bitcount尽量大的子集
    table.clear();
    int n1 = n/2, n2 = n-n1;
    for(int i = 0; i < (1<<n1); i++) {
      int x = 0;
      for(int j = 0; j < n1; j++) if(i & (1<<j)) x ^= A[j];
      if(!table.count(x) || bitcount(table[x]) < bitcount(i)) table[x] = i;
    }
    // 枚举后n2个元素的所有子集，并在table中查找
    int ans = 0;
    for(int i = 0; i < (1<<n2); i++) {
      int x = 0;
      for(int j = 0; j < n2; j++) if(i & (1<<j)) x ^= A[n1+j];
      if(table.count(x)&&bitcount(ans)<bitcount(table[x])+bitcount(i)) ans = (i<<n1)^table[x];
    }
    // 输出结果
    printf("%d\n", bitcount(ans));
    for(int i = 0; i < n; i++) if(ans & (1<<i)) printf("%d ", i+1);
    printf("\n");
  }
  return 0;
}
