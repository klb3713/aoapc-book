// Uva1510 Neon Sign (LA5846)
// 陈锋
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 1000 + 10, RED = 1, BLUE = 0;
int blue[maxn], red[maxn];
void runcase(int t)
{    
    int N, color;
    scanf("%d", &N);
    
    fill_n(blue, N, 0);
    fill_n(red, N, 0);
    
    for(int i = 0; i < N - 1; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            scanf("%d", &color);           
            red[i] += (color == RED);
            blue[i] += (color == BLUE);
            red[j] += (color == RED);
            blue[j] += (color == BLUE);
        }
    }
    
    int sum = 0;
    for(int i = 0; i < N; i++)
        sum += red[i] * blue[i];
    
    int result = N * (N - 1) * (N - 2) / 6 - sum / 2;
    printf("%d\n", result);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++)
        runcase(t+1);
    return 0;
}