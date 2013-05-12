// UVa10055 Hashmat the brave warrior
// Rujia Liu
// 注意事项：输入超过了带符号32位整数的范围，需要用无符号整数或者64位整数
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
  long long a, b;
  while(cin >> a >> b) cout << abs(a-b) << "\n";
  return 0;
}
