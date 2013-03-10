// UVa10090 Marbles
// 陈锋
#include<cstring>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long longInt;

longInt n, c1, n1, c2, n2;

void gcd(longInt a, longInt b, longInt& d, longInt& x, longInt& y)
{
    if(b == 0) 
    {
        d = a; x = 1; y = 0;
    }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= x * (a/b);
    }
}

void runcase()
{    
    // 先求方程 n1 * x + n2 * y = gcd(n1, n2) 的整数解
    longInt g, x, y;
    gcd(n1, n2, g, x, y);
    if( n % g != 0 ) 
    {
        cout<<"failed"<<endl;
        return;
    }
    
    x *= n / g, y *= n / g;
    // 方程的所有整数解都可以写成 x + k * n2/g, y - k * n1/g, 接下来求出让这两个数都 >=0 的k的范围
    // x + k*n2/g >= 0 -> k >= - x / (n2/g)
    // y - k*n1/g >= 0 -> k <= y / (n1/g)
    longInt minK = ceil(- ((double)x) / (n2 / g)), maxK = floor(((double)y) / (n1 / g));
    if(minK > maxK)
    {
        cout<<"failed"<<endl;
        return;
    }
    
    // 若 c1 * n2 <= c2 * n1，此种情况下 x 越大花费越少，则 k 取上限。反之 k 取下限，x 越小花费越少。等于的情况可放到任意一个情况中，因为所产生费用相当。
    if (c1 * n2 <= c2 * n1)  
    {  
        x = n2 / g * maxK + x;  
        y = y - n1 / g * maxK;  
    }  
    else  
    {  
        x = n2 / g * minK + x;  
        y = y - n1 / g * minK;  
    }  
      
    cout << x << " " << y << endl;  
}

int main() {
    while(true)
    {
        cin>>n>>c1>>n1>>c2>>n2;        
        if(n == 0) break;
        runcase();
    }
    return 0;
}