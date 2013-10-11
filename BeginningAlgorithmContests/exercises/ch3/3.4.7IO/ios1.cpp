#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1000000];
int main(){
  freopen("ios.in", "r", stdin);
  freopen("ios1.out", "w", stdout);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i=1; i<=n; i++) cin >> a[i];
  sort(a+1, a+n+1);
  for (int i=1; i<=n; i++) cout << a[i] <<" ";
  cout << endl;
}
