// UVa10387 Billiard
// Rujiu Liu
// 题意：a*b的矩形中心有一个球，沿着某方向匀速运动，s秒后回到中点，途中和左右边界碰撞m次、和上下边界碰撞n次。碰撞时遵守反射定律，没有能量损失。求速度的极角和大小
// 算法：分开计算速度的水平和竖直分量即可。比如水平方向走了m个来回，因此距离为a*m，除以时间s，得到水平方向速度am/s
#include<cstdio>
#include<cmath>
const double PI = acos(-1.0);
int main() {
    int a, b, s, m, n;
    while(scanf("%d%d%d%d%d", &a, &b, &s, &m, &n) == 5 && a) {
        double vx = (double)a * m / s, vy = (double)b * n / s;
        printf("%.2lf %.2lf\n", atan2(vy, vx) / PI * 180, sqrt(vx*vx+vy*vy));
    }
    return 0;
}
