// UVa10790 How Many Points of Intersection?
// Rujia Liu
// 题意：两条平行直线，上面有a个点，下面有b个点。两两连接之后最多会有多少个交点？
// 算法：上面第i个点和下面第j个点组成的线段与哪些线段相交呢？上端点一定是第i个点左边（i-1种），下端点一定是第j个点右边（b-j种），求和整理即可

#include<cstdio>
int main() {
  int kase = 0, a, b;
  while(scanf("%d%d", &a, &b) == 2 && a)
    printf("Case %d: %lld\n", ++kase, (long long)a*(a-1)*b*(b-1)/4);
  return 0;
}
