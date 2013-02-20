// UVa10081 Tight words
// 陈锋
#include<cstring>
#include<iostream>
#include <iomanip>
#include<cmath>
#include<algorithm>
using namespace std;
int k, n;
const int MAXK = 9, MAXN = 100;
double dp[MAXK + 10][MAXN + 10];
bool vis[MAXK + 10][MAXN + 10];

double calc(int c, int n)
{
    if(c > k || c < 0) return 0;
    double& ans = dp[c][n];
    if(vis[c][n]) return ans;
    
    if(n == 1)
        ans = 1;
    else
        ans = calc(c - 1, n - 1) + calc(c, n - 1) + calc(c + 1, n - 1);
    
    vis[c][n] = true;
    
    return ans;
}

void runcase()
{    
    memset(vis, false, sizeof(vis));
    double ans = 0;
    for(int i = 0; i <= k; i++)
        ans += calc(i, n);
    ans /= pow(k + 1, n);
    
    ans *= 100;
    cout.precision(5);
    cout<<fixed<<ans<<endl;
}

/*
    总的样本空间数字是kn。
    定义DP(k, n)为以k为最后一个字符的长度为n的单词的数量。
    则DP(k,n) = DP(k-1, n-1) + DP(k + 1, n-1) + DP(k, n-1)。
    当k 越界的时候，返回0。当n = 1的时候，返回1。
    这个DP定义为double以避免溢出。
    最终所求的答案为100 * (∑DP(i,n) for i = 0 to k)/(k+1)^n。
*/

int main() {
    ios_base::sync_with_stdio(false);
    while(cin>>k>>n)
    {
        runcase();
    }
    return 0;
}