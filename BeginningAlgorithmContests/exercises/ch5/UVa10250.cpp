// UVa10250 The Other Two Trees
// Rujia Liu
// 题意：输入正方形两个对角顶点P1, P2，求另外两个点的坐标
// 算法：先求中点O，然后分别把向量P1-O逆时针旋转90度和-90度，与O相加
// 向量(vx,vy)逆时针旋转90度为(-vy,vx)，顺时针转90度为(vy,-vx)
#include<cstdio>
int main() {
    double x1, y1, x2, y2;
    while(scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2) == 4) {
        if(x1 == x2 && y1 == y2) printf("Impossible.\n");
        else {
            double ox = (x1 + x2) / 2, oy = (y1 + y2) / 2; // 中点
            double vx = x1 - ox, vy = y1 - oy; // 向量v = p1 - o
            printf("%.10lf %.10lf %.10lf %.10lf\n", ox-vy, oy+vx, ox+vy, oy-vx);
        }
    }
    return 0;
}
