// UVa10071 Back to High School Physics
// Rujia Liu
// 题意：一个粒子初速度为v0，恒定加速度为a。已知时间t后速度为v，求再过时间t后的总位移
// 算法：根据几何意义知总位移是梯形面积，它等于中位线乘以高，即2vt

#include<iostream>
using namespace std;
int main() {
  int v, t;
  while(cin >> v >> t) cout << 2*v*t << "\n";
  return 0;
}
