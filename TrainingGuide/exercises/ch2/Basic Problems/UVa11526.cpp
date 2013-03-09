// UVa11526 H(n)
// Rujia Liu

#include<cstdio>

long long H(int n){
  if(n <= 0) return 0;
  long long res = 0;
  unsigned int last;
  for(unsigned int i = 1; i <= n; i = last+1){
    last = n/(n/i);
    res = (res + n/i*(last-i+1));
  }
  return res;
}

int main() {
  int n, T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    printf("%lld\n", H(n));
  }
  return 0;
}