#include<cstdio>
#include<algorithm>
using namespace std;
int v[10000];
int main(){
  int n, m, a, b;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) scanf("%d", &v[i]);
  sort(v, v+n);
  for(int i = 0; i < m; i++){
    scanf("%d%d", &a, &b);
    printf("%d\n", upper_bound(v, v+n, b)-lower_bound(v, v+n, a));
  }
}
