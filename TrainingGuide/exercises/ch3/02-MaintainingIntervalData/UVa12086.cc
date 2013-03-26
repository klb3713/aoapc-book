// LA2191(UVa12086) Potentiometers
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

typedef long long int64;

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

inline int lowbit(int x) { return x&-x; }

struct FenwickTree {
  int n;
  vector<int64> C;

  void resize(int n) { this->n = n; C.resize(n+1); }
  void clear() { fill(C.begin(), C.end(), 0); }

  // 计算A[1]+A[2]+...+A[x] (x<=n)
  int64 sum(int x) {
    int64 ret = 0;
    while(x > 0) {
      ret += C[x]; x -= lowbit(x);
    }
    return ret;
  }

  // A[x] += d (1<=x<=n)
  void add(int x, int d) {
    while(x <= n) {
      C[x] += d; x += lowbit(x);
    }
  }
};

const int MAXN = 200000 + 10;
int N, data[MAXN];
FenwickTree f;

void set(int x, int y)
{
    // printf("set %d = %d\n", x, y);
    f.add(x, y - data[x]);
    data[x] = y;
}

void measure(int x, int y)
{
    // printf("measure %d =-> %d  ", x, y);
    int64 ans = f.sum(y) - f.sum(x - 1);
    printf("%lld\n", ans);
}


int main()
{
    int k = 1;
    while(true)
    {
        N = readint();
        if(N == 0) break;
        if(k > 1) puts("");
        printf("Case %d:\n", k++);
        
        f.resize(N);
        f.clear();
        
        for(int i = 1; i <= N; i++)
        {
            int x = readint();
            f.add(i, x);
            data[i] = x;
        }
        
        while(true)
        {
            char buf[16];
            scanf("%s", buf);
            if(buf[0] == 'E') break;
            int x = readint(), y = readint();
            
            scanf("%d%d", &x, &y);
            if(buf[0] == 'S')
                set(x, y);
            else if(buf[0] == 'M')
                measure(x, y);
        }
    }
    
    return 0;
}
