// UVa11729 Commando War
// Rujia Liu
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Job {
  int j, b;
  bool operator < (const Job& x) const { // 运算符重载。不要忘记const修饰符
    return j > x.j;
  }
};

int main() {
  int n, b, j, kase = 1;
  while(scanf("%d", &n) == 1 && n) {
    vector<Job> v;
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &b, &j); v.push_back((Job){j,b});
    }
    sort(v.begin(), v.end()); //使用Job类自己的 < 运算符排序
    int s = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
      s += v[i].b;  //当前任务的开始执行时间
      ans = max(ans, s+v[i].j);	//更新任务执行完毕时的最晚时间
    }
    printf("Case %d: %d\n", kase++, ans);
  }
  return 0;
}
