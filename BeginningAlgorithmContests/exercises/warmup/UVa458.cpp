// UVa458 The Decoder
// Rujia Liu
#include<iostream>
#include<string>
using namespace std;

int main() {
  string s;
  while(cin >> s) {
    for(int i = 0; i < s.length(); i++) s[i] -= 7;
    cout << s << "\n";
  }
  return 0;
}