// UVa10079 Pizza Cutting
// Rujia Liu
#include<iostream>
using namespace std;

int main() {
  long long n;
  while(cin >> n && n >= 0) {
    cout << n*(n+1)/2+1 << "\n";
  }
  return 0;
}
