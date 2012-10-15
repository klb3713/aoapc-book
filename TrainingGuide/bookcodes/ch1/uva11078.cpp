// UVa11078 Open Credit System
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;
int A[100000], n;
int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    int ans = A[0]-A[1];
    int MaxAi = A[0]; // MaxAi动态维护A[0]，A[1]，…，A[j-1]的最大值
    for(int j = 1; j < n; j++) { // j从1而不是0开始枚举，因为j=0时，不存在i
      ans = max(ans, MaxAi-A[j]);
      MaxAi = max(A[j], MaxAi); //MaxAi晚于ans更新。想一想，为什么
    }
    printf("%d\n", ans);
  }
  return 0;
}
