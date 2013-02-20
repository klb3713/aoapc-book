// Uva10883 Supermean
// 陈锋
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn = 50000 + 10;

void runcase(int t)
{    
    int n;
    scanf("%d", &n);
    double sum = 0, lgc = 0, logd = (n-1) * log(2), num;

    for(int i = 0; i < n; i++)
    {
        scanf("%lf", &num);
        if(i) lgc += log(n-i) - log(i); // 计算的精度问题
        
        if(num > 0.0)
            sum += exp(lgc + log(num) - logd);
        else if(num < 0.0)
            sum -= exp(lgc + log(-num) - logd);
    }
    
    printf("Case #%d: %.3lf\n", t, sum);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++)
        runcase(t+1);
    return 0;
}

/*
简单计算不难发现对于输入的x1 x2 ... xn，连续计算之后，各个xi的系数实际上形成一个杨辉三角，也就是说最终答案是(Σxi * C(n, i)) / (2^(n-1))。因为分子分母里面的系数都太大，直接计算必然会溢出，所以可以先求对数，再求exp。这里需要特别注意的是，输入的数字有可能是负数或者0，在求对数的时候需要进行特殊处理。
*/