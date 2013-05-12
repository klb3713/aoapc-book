// UVa10300 Ecological Premium
// Rujia Liu
// 题意：输入n个三元组(a,b,c)，计算a*c之和
// 注意事项：观察题目中的数值范围可以发现结果需要用long long保存
#include<iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  while(T--) {
    long long n, a, b, c, sum = 0;
    cin >> n;
    while(n--) { cin >> a >> b >> c; sum += a * c; }
    cout << sum << "\n";
  }
  return 0;
}
