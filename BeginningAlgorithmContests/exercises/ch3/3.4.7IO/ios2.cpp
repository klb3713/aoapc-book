#include<cstdio>
#include<algorithm>
using namespace std;
int a[1000000];
int main(){
  freopen("ios.in", "r", stdin);
  freopen("ios2.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) scanf("%d", a+i);
  sort(a+1, a+n+1);
  for (int i=1; i<=n; i++) printf("%d ", a[i]);
  putchar('\n');
}
