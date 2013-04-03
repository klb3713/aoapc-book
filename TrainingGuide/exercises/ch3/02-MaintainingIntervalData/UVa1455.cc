// LA4730(UVa1455) – Kingdom
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <climits>
#include <vector>

using namespace std;

typedef long long int64;

using namespace std;

template<int maxnode>
struct IntervalTree {
  int sumv[maxnode], addv[maxnode], _sum, qL, qR, v, n;
  
  void Add(int value, int L, int R)
  {
    v = value;
    qL = L + 1;
    qR = R + 1;
    update(1, 1, n);
  }
  
  int query(int L, int R)
  {
    _sum = 0;
    qL = L + 1;
    qR = R + 1;
    query(1, 1, n, 0);
    return _sum;
  }
  
  void init(int size)  
  {
    memset(this, 0, sizeof(IntervalTree));
    n = size;
  }

  // 维护信息
  void maintain(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    sumv[o] = 0;
    if(R > L) {
      sumv[o] = sumv[lc] + sumv[rc];
    }
    if(addv[o]) { sumv[o] += addv[o] * (R-L+1); }
  }

  void update(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(qL <= L && qR >= R) { // 递归边界      
      addv[o] += v; // 累加边界的add值
    } else {
      int M = L + (R-L)/2;
      if(qL <= M) update(lc, L, M);
      if(qR > M) update(rc, M+1, R);
    }
    maintain(o, L, R); // 递归结束前重新计算本结点的附加信息
  }

  void query(int o, int L, int R, int add) {
    // printf("query: o = %8d, L = %d, R = %d, qL = %d, qR = %d, addv = %d, sum = %d\n", o, L, R, qL, qR, addv[o], _sum);
  
    if(qL <= L && qR >= R) { // 递归边界：用边界区间的附加信息更新答案
      _sum += sumv[o] + add * (R-L+1);
    } else { // 递归统计，累加参数add
      int M = L + (R-L)/2;
      if(qL <= M) query(o*2, L, M, add + addv[o]);
      if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
    }
  }
};

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

struct City
{
    int y, minY, maxY, size;
    City *ppa;
    
    City* getPa()
    {
        City *p = ppa;
        while(p != p->ppa)
            p = p->ppa;
        return ppa = p;
    }
};

static const int maxn = 100000 + 10, MAXC = 1000000;
City cities[maxn];
IntervalTree<MAXC*2> tree1, tree2;

void connect(int A, int B)
{
    City *paA = cities[A].getPa(), *paB = cities[B].getPa();
    if(paA == paB) return;
    
    assert(paB->minY <= paB->maxY);
    
    if(paB->minY != paB->maxY)
    {
        tree1.Add(-1, paB->minY, paB->maxY - 1);
        tree2.Add(-paB->size, paB->minY, paB->maxY - 1);
    }
    if(paA->minY != paA->maxY)
    {
        tree1.Add(-1, paA->minY, paA->maxY - 1);
        tree2.Add(-paA->size, paA->minY, paA->maxY - 1);
    }
     
    paA->size += paB->size;
    paB->ppa = paA;
    paA->minY = min(paA->minY, paB->minY);
    paA->maxY = max(paA->maxY, paB->maxY);
    assert(paA->minY <= paA->maxY);
    
    if(paA->minY != paA->maxY)
    {
        tree1.Add(1, paA->minY, paA->maxY - 1);
        tree2.Add(paA->size, paA->minY, paA->maxY - 1);
    }
}

void solve()
{
    int n = readint();
    tree1.init(MAXC);
    tree2.init(MAXC);
    
    int i = 0;
    for(i = 0; i < n; i++)
    {
        City *p = &(cities[i]);
        readint();
        p->y = readint();
        p->ppa = p;
        p->minY = p->y;
        p->maxY = p->y;
        p->size = 1;
    }
    
    int m = readint();
    char cmd[16];    
    for(i = 0; i < m; i++)
    {
        scanf("%s", cmd);
        if(cmd[0] == 'r')
        {
            int A, B;
            A = readint(), B = readint();            
            connect(A, B);
        }
        else if(cmd[0] = 'l')
        {
            float C;
            scanf("%f", &C);
            int y = (int)C;
            pair<int, int> sd = make_pair(tree1.query(y, y), tree2.query(y, y));
            printf("%d %d\n", sd.first, sd.second);
        }
    }
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
        solve();

    return 0;
}