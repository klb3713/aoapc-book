// UVa101 The Blocks Problem
// Rujia Liu
/*
  题意：
  从左到右有n个木块，编号为0~n-1，要求模拟一些操作，有四种（下面的a和b都是木块编号）：
  move a onto b：把a和b上方的木块全部归位，然后把a摞在b上面
  move a over b：把a上方的木块全部归位，然后把a放在b所在木块堆的顶部
  pile a onto b：把b上方的木块全部归位，然后把a及上面的木块整体摞在b上面
  pile a over b：把a及上面的木块整体摞在b所在木块堆的顶部
  遇到quit时终止一组数据。a和b在同一堆的指令是非法指令，应当忽略。
*/

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

// 找木块a所在的pile和height
void find_block(int a, int& p, int& h) {
  for(p = 0; p < n; p++)
    for(h = 0; h < pile[p].size(); h++)
      if(pile[p][h] == a) return;
}

void clear_above(int p, int h) {
  for(int i = h+1; i < pile[p].size(); i++) {
    int b = pile[p][i];
    pile[b].push_back(b); // 把木块b放回原位
  }
  pile[p].resize(h+1);
}

// 把第p堆高度h及其上方的木块整体移动到p2堆的顶部
void pile_onto(int p, int h, int p2) {
  for(int i = h; i < pile[p].size(); i++)
    pile[p2].push_back(pile[p][i]);
  pile[p].resize(h);
}

void print() {
  for(int i = 0; i < n; i++) {
    printf("%d:", i);
    for(int j = 0; j < pile[i].size(); j++) printf(" %d", pile[i][j]);
    printf("\n");
  }  
}

int main() {
  int a, b;
  cin >> n;
  string s1, s2;
  for(int i = 0; i < n; i++) pile[i].push_back(i);
  while(cin >> s1 >> a >> s2 >> b) {
    int pa, pb, ha, hb;
    find_block(a, pa, ha);
    find_block(b, pb, hb);
    if(pa == pb) continue; // 非法指令
    if(s2 == "onto") clear_above(pb, hb);
    if(s1 == "move") clear_above(pa, ha);
    pile_onto(pa, ha, pb);
  }
  print();
  return 0;
}
