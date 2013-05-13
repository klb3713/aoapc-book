// UVa10585 Center of Symmetry
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#include<utility>
#include<climits>
using namespace std;

int readint() {
    int x;
    scanf("%d", &x);
    return x;
}

const int maxn = 10000 + 10;
int x[maxn], y[maxn];
set<pair<int, int> > S;

void solve(){
    int n = readint();
    int minx = LONG_MAX, maxx = LONG_MIN , miny = LONG_MAX, maxy = LONG_MIN;
    S.clear();
    
    for(int i = 0; i < n; i++) {
        int& a = x[i];
        int& b = y[i];
        a = readint() * 2;
        b = readint() * 2;
        S.insert(make_pair(a, b));
    
        minx = min(minx, a);
        maxx = max(maxx, a);
        miny = min(miny, b);
        maxy = max(maxy, b);
    }
    
    int symx = minx + maxx, symy = miny + maxy;
    for(set<pair<int, int> >::iterator it = S.begin(); it != S.end(); it++) {
        pair<int, int> sym = make_pair(symx - it->first, symy - it->second);
        if(!S.count(sym)) { puts("no"); return; }
    }
    
    puts("yes");
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
        solve();
    
    return 0;
}