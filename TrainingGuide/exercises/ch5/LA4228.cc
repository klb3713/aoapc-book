// LA4288  Cat vs. Dog
// 陈锋
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXPET = 300, maxn = 500 + 5; // 单侧顶点的最大数目;

struct Voter
{
    string love, hate;
    void read()
    {
        cin>>love>>hate;
    }
    
    bool conflict(const Voter& rhs) const
    {
        return love == rhs.hate || hate == rhs.love;
    }
};

Voter voters[maxn];

// 二分图最大基数匹配，邻接矩阵写法
struct BPM {
  int n, m;               // 左右顶点个数
  int G[maxn][maxn];      // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u){
    for(int v = 0; v < m; v++) if(G[u][v] && !T[v]) {
      T[v] = true;
      if (left[v] == -1 || match(left[v])){
        left[v] = u;
        return true;
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    memset(left, -1, sizeof(left));
    int ans = 0;
    for(int u = 0; u < n; u++) { // 从左边结点u开始增广
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

};

BPM solver;

void runcase()
{
    int c, d, v, x, y;
    cin>>c>>d>>v;
    vector<int> cat_lovers, dog_lovers;
    for(int i = 0; i < v; i++)
    {
        Voter& voter = voters[i];
        voter.read();
        if(voter.love[0] == 'C')
            cat_lovers.push_back(i);
        else
            dog_lovers.push_back(i);
    }
    x = cat_lovers.size();
    y = dog_lovers.size();
    
    solver.init(cat_lovers.size(), dog_lovers.size());
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            if(voters[cat_lovers[i]].conflict(voters[dog_lovers[j]])) solver.G[i][j] = 1;
    
    cout<<(x + y - solver.solve())<<endl;
}

int main() {
    int T;
    cin>>T;
    for(int i = 1; i <= T; i++)
        runcase();
    return 0;
}