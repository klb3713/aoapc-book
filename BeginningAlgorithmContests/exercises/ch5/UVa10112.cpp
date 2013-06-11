// UVa10112 Myacm Triangles
// Rujia Liu
// 题意：输入平面上n<=15个点，找一个三角形，使得内部没有其他点，并且面积最大
// 算法：暴力枚举+判断点在三角形内（《入门经典》第5章有讲，虽然速度稍慢，但够用）
// 如果事先算出所有三角形的面积，速度会略有提升，留给读者实现
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 20;
char name[maxn][5], ans[4];
int n, best, x[maxn], y[maxn];

int area2(int a, int b, int c) {
  return abs(x[a]*y[c]+x[b]*y[a]+x[c]*y[b]-x[b]*y[c]-x[c]*y[a]-x[a]*y[b]);
}

void check_triangle(int a, int b, int c) {
    int a2 = area2(a, b, c);
    for(int i = 0; i < n; i++)
        if(i != a && i != b && i != c && area2(a, b, i) + area2(b, c, i) + area2(c, a, i) == a2) return;
    if(a2 > best) {
        best = a2;
        ans[0] = name[a][0], ans[1] = name[b][0], ans[2] = name[c][0];
        sort(ans, ans+3); // 输出的三个字母必须按照升序排列
    }
}

int main() {
    ans[3] = '\0';
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++) scanf("%s%d%d", name[i], &x[i], &y[i]);
        best = -1;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                for(int k = j+1; k < n; k++)
                    check_triangle(i, j, k);
        printf("%s\n", ans);
    }
    return 0;
}
