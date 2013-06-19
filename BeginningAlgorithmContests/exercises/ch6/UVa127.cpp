// UVa127 "Accordian" Patience
// Rujia Liu
/*

题意：

  把52张牌从左到右排好，每张牌自成一个牌堆(pile)。
  当某张牌与它左边那张牌或者左边第三张牌“match”（花色suit或者点数rank相同）的时候，就把这张牌移到那张牌上面去。
  移动之后还要看看是否可以进行其他的移动。只有位于牌堆顶部的牌才能移动或者参与match。
  当牌堆之间出现空隙的时候要立刻把右边的所有牌堆左移一格来填补空隙。
  如果有多张牌可以移动，先移动最左边的那张牌；如果既可以移一格也可以移三格的时候，移三格。 

算法：每堆牌是一个栈，各个牌堆形成一个链表。为了方便判断和存储，牌(rank, suit)转化成整数rank*4+suit

*/

#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int ncard = 52;

struct Pile {
  int t;
  int cards[ncard];
  int next, prev;
  int top() const { return cards[t]; }
  int pop() { return cards[t--]; }
  void push(int v) { cards[++t] = v; }
  bool empty() const { return t == -1; }
} pile[ncard+1]; // pile[52]是虚拟堆

const char* suits = "CDHS";
const char* ranks = "A23456789TJQK";

int card2int(char r, char s) {
  int suit = strchr(suits, s) - suits;
  int rank = strchr(ranks, r) - ranks;
  return rank*4+suit;
}

bool read_input() {
  char card[5];
  for(int i = 0; i < ncard; i++) {
    if(scanf("%s", card) != 1) return false;
    pile[i].cards[0] = card2int(card[0], card[1]);
    pile[i].t = 0;
    pile[i].prev = i-1;
    pile[i].next = i+1;
  }
  return true;
}

// 第p堆左边k堆的编号
int left(int p, int k) {
  while(k--) {
    p = pile[p].prev;
    if(p < 0) return -1;
  }
  return p;
}

inline int match(int card1, int card2) {
  return card1 % 4 == card2 % 4 || card1 / 4 == card2 / 4;
}

// 牌堆p顶部的牌是否可以移动
bool can_move(int p) {
  int card = pile[p].top();
  int p1 = left(p, 1);
  int p3 = left(p, 3);
  if(p3 >= 0 && match(card, pile[p3].top())) return true;
  if(p1 >= 0 && match(card, pile[p1].top())) return true;
  return false;
}

void move(int p) {
  int card = pile[p].top();
  int cur = p;
  for(;;) {
    int p1 = left(cur, 1);
    int p3 = left(cur, 3);
    if(p3 >= 0 && match(card, pile[p3].top())) { cur = p3; continue; }
    if(p1 >= 0 && match(card, pile[p1].top())) { cur = p1; continue; }
    break;
  }
  // 从p移动到cur
  pile[p].pop();
  pile[cur].push(card);
  if(pile[p].empty()) {
    int left = pile[p].prev, right = pile[p].next;
    pile[left].next = right; pile[right].prev = left;
  }
}

int main() {
  for(;;) {
    if(!read_input()) break;
    for(;;) {
      // 找一张可以移动的牌
      int p = 0;
      while(p < ncard) {
        if(can_move(p)) break;
        p = pile[p].next;
      }
      if(p == ncard) break; // 无牌可以移动
      move(p);
    }

    // 输出
    vector<int> ans;
    int p = 0;
    while(p < ncard) {
      ans.push_back(pile[p].t+1);
      p = pile[p].next;
    }
    int n = ans.size();
    printf("%d pile", n);
    if(n > 1) printf("s");
    printf(" remaining:");
    for(int i = 0; i < n; i++) printf(" %d", ans[i]);
    printf("\n");
  }
  return 0;
}
