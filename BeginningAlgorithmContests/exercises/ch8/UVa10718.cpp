// UVa10718 Bit Mask
// Rujia Liu
// 题意：给你一个32位的非负整数N。找出一个数M，满足L<=M<=U并且N or M的值最大。比如说，N=100，L=50，U=60，那么M=59时，N or M = 127最大。如果有几个M同时满足条件，输出最小的一个M。 
// 算法：贪心，最长的32位，从左边开始做起，每一位都有唯一的贪心填法，保证or N为max的同时，使填的答案在L,U 范围内即可。 
#include<iostream>
using namespace std;

// 两个区间[left, right], [L, U]是否有交集
inline bool overlap(long long left, long long right, long long L, long long U) {
  return !(right < L || U < left);
}

int main() {
  long long N, L, U, M;
  while(cin >> N >> L >> U) {
    M = 0;
    for(int i = 31; i >= 0; i--) {
      long long bit = 1LL << i;
      bool ok0 = overlap(M, M + bit - 1, L, U); // 是否可以填0
      bool ok1 = overlap(M + bit, M + bit * 2 - 1, L, U); // 是否可以填1
      if((!ok0 && ok1) || (ok0 && ok1 && !(N & bit))) M ^= bit; // (1) 只能填1或者 (2)01都行但N的对应位为0，则必须填1
    }
    cout << M << "\n";
  }
  return 0;
}
