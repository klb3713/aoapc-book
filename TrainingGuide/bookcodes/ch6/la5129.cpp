// LA5129/UVa1102 Affine Mess
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

/*
  求解下列方程组的整数解的个数：
  p*s + d = x
  q*s + d = y
  r*s + d = z
  其中s代表缩放系数，d代表平移量

  解：联立方程(1), (2)，得(p-q)*s = x-y
  i) 如果p-q = 0，则必须有x == y，否则无解
  ii) 如果p-q != 0，则s = (x-y)/(p-q)。如果s不是整数则无解，否则s是一个解

  类似的，还应联立(2), (3)和(3), (1)求解。
  i) 如果求出了多个s，他们必须相同；
  ii) 如果一个s都没有得到，说明有无穷多解（返回2就可以了）
  iii) 如果s = 0，根据题意，也无解
*/
int solve(int p, int q, int r, int x, int y, int z) {
  int a[] = {p, q, r};
  int b[] = {x, y, z};
  vector<int> ans;
  for(int i = 0; i < 3; i++) {
    int P = a[i], Q = a[(i+1)%3], X = b[i], Y = b[(i+1)%3];
    if(P == Q) { if(X != Y) return 0; }
    else if((X - Y) % (P - Q) != 0) return 0;
    else ans.push_back((X - Y) / (P - Q));
  }
  if(ans.empty()) return 2; // 三个方程等价，无穷多组解
  sort(ans.begin(), ans.end());
  if(ans[0] != ans.back() || ans[0] == 0) return 0; // 求出的s不全相同或者等于0
  return 1;
}

int x[3], y[3]; // 变换前的点
int x2[3], y2[3]; // 变换后的点
int ix[3], iy[3]; // 旋转+捕捉f后的点

int main() {
  int kase = 0;
  for(;;) {
    int ok = 0;
    for(int i = 0; i < 3; i++) {
      scanf("%d%d", &x[i], &y[i]);
      if(x[i] != 0 || y[i] != 0) ok = 1;
    }
    if(!ok) break;
    for(int i = 0; i < 3; i++) scanf("%d%d", &x2[i], &y2[i]);
    int ans = 0; // 解的个数

    // 枚举旋转方式
    // 注意旋转180度等价于缩放(-1,-1)，所以只枚举40个点而不是80个
    for(int i = 0; i < 40; i++) {
      int rx, ry;
      if(i < 20) { rx = 10; ry = i - 10; } // (10,-10), (10,-9), ..., (10,9), (10,9)
      else { rx = 30 - i; ry = 10; } // (10,10), (9,10), ..., (-9,10)

      // 变换前3个点，保存在(ix[i],iy[i])中
      double len = sqrt(rx*rx+ry*ry);
      double cosa = rx / len;
      double sina = ry / len;
      int ix[3], iy[3];
      for(int j = 0; j < 3; j++) {
        ix[j] = (int)floor(x[j] * cosa - y[j] * sina + 0.5);
        iy[j] = (int)floor(x[j] * sina + y[j] * cosa + 0.5);
      }

      // 枚举(ix, iy)和(x2, y2)的对应关系
      int p[3] = {0, 1, 2};
      do {
        int cnt1 = solve(ix[0], ix[1], ix[2], x2[p[0]], x2[p[1]], x2[p[2]]);
        int cnt2 = solve(iy[0], iy[1], iy[2], y2[p[0]], y2[p[1]], y2[p[2]]);
        ans += cnt1 * cnt2; // x, y方向独立，分别求解
      } while(next_permutation(p, p+3));
    }

    printf("Case %d: ", ++kase);
    if(ans == 0) printf("no solution\n");
    else if(ans == 1) printf("equivalent solutions\n");
    else printf("inconsistent solutions\n");
  }
  return 0;
}
