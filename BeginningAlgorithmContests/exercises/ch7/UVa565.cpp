// UVa565 Pizza Anyone?
// Rujia Liu
// 题意：有A~P共16种，有n个形如+A-B+D的约束（表示要A或者不要B或者要D）。求一种方案满足所有约束
// 算法：回溯法
// 提示：本题数据较多，直接2^16子集枚举会超时。回溯法可以避免无用的枚举，详见注释
// 本题还有一个方法，即搜索各个约束的满足方式，而不是搜索每个字母要还是不要，读者可以一试
#include<cstdio>
#include<cstring>
const int C = 'P' - 'A' + 1;
int n;
int mask[C][2]; // mask[i][v]表示第i个字母取v（0或者1）时，可以直接满足的约束集合

bool dfs(int d, int used, int satisfied) {
  if(d == C) {
    if(satisfied < (1<<n) - 1) return false;
    printf("Toppings: ");
    for(int i = 0; i < C; i++) if(used & (1<<i)) printf("%c", 'A'+i);
    printf("\n");
    return true;
  }
  int m0 = satisfied | mask[d][0];
  int m1 = satisfied | mask[d][1];
  if(dfs(d+1, used, m0)) return true;
  if(m0 != m1 && dfs(d+1, used | (1<<d), m1)) return true; // 避免无用枚举。这个优化虽然简单但效果非常好
  return false;
}

bool init() {
  n = 0;
  memset(mask, 0, sizeof(mask));
  for(;;) {
    char line[50];
    if(scanf("%s", line) != 1) return false;
    if(line[0] == '.') return true;
    for(int i = 0; i < strlen(line)-1; i += 2) {
      int elem = line[i+1] - 'A';
      int v = line[i] == '+' ? 1 : 0;
      mask[elem][v] |= 1 << n;
    }
    n++;
  }
}

int main() {
  for(;;) {
    if(!init()) break;
    if(!dfs(0, 0, 0)) printf("No pizza can satisfy these requests.\n");
  }
  return 0;
}
