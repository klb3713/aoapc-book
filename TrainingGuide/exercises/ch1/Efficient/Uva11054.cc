// Uva11054	Wine trading in Gergovia
// ³Â·æ
#include <algorithm>
#include <iostream>

#define ABS(a)       (((a) < 0) ? -(a) : (a))

using namespace std;

inline int readint()
{
    int num;
    cin>>num;
    return num;
}

const int MAXN = 100352;
int a[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    while(true)
    {
        int n;
        long long minunit, sum;
        
        n = readint();
        if(n == 0) break;
        minunit = sum = 0;
        
        for(int i = 0; i < n; i++)
        {
            a[i] = readint();
            minunit += ABS(sum);
            sum += a[i];
        }
        
        cout<<minunit<<endl;
    }
    
    return 0;
}
