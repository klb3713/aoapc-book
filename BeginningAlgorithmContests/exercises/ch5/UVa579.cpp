// UVa579 ClockHands
// Rujia Liu
// 题意：注意题目最后一段的开头：The history of clocks is fascinating, but unrelated to this problem，所以前面都不用读。
// 输入时间，求时针和分针的夹角（转化为最小正数）。注意，时针是连续的走（每小时1格，则每分钟1/60格，即0.5度）
// 算法：a点b分，时针的极角为a*30+b*0.5，分针的极角为6*b
#include<cstdio>
int main() {
    int a, b;
    while(scanf("%d:%d", &a, &b) == 2 && (a || b)) {
        double d = a*30+b*0.5 - 6*b;
        if(d < 0) d = -d; // 调整为正数
        if(360 - d < d) d = 360 - d; // 变小
        printf("%.3lf\n", d);
    }
    return 0;
}
