// UVa11922 Permutation Transformer
// Rujia Liu
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Node {
  Node *ch[2];
  int s;
  int flip;
  int v;
  int cmp(int k) const {
    int d = k - ch[0]->s;
    if(d == 1) return -1;
    return d <= 0 ? 0 : 1;
  }
  void maintain() {
    s = ch[0]->s + ch[1]->s + 1;
  }
  void pushdown() {
    if(flip) {
      flip = 0;
      swap(ch[0], ch[1]);
      ch[0]->flip = !ch[0]->flip;
      ch[1]->flip = !ch[1]->flip;
    }
  }
};

Node *null = new Node();

void rotate(Node* &o, int d) {
  Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
  o->maintain(); k->maintain(); o = k; 
}

void splay(Node* &o, int k) {
  o->pushdown();
  int d = o->cmp(k);
  if(d == 1) k -= o->ch[0]->s + 1;
  if(d != -1) {
    Node* p = o->ch[d];
    p->pushdown();
    int d2 = p->cmp(k);
    int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
    if(d2 != -1) {
      splay(p->ch[d2], k2);
      if(d == d2) rotate(o, d^1); else rotate(o->ch[d], d);
    }
    rotate(o, d^1);
  }
}

// 合并left和right。假定left的所有元素比right小。注意right可以是null，但left不可以
Node* merge(Node* left, Node* right) {
  splay(left, left->s);
  left->ch[1] = right;
  left->maintain();
  return left;
}

// 把o的前k小结点放在left里，其他的放在right里。1<=k<=o->s。当k=o->s时，right=null
void split(Node* o, int k, Node* &left, Node* &right) {
  splay(o, k);
  left = o;
  right = o->ch[1];
  o->ch[1] = null;
  left->maintain();
}

const int maxn = 100000 + 10;
struct SplaySequence {
  int n;
  Node seq[maxn];
  Node *root;

  Node* build(int sz) {
    if(!sz) return null;
    Node* L = build(sz/2);
    Node* o = &seq[++n];
    o->v = n; // 节点编号
    o->ch[0] = L;
    o->ch[1] = build(sz - sz/2 - 1);
    o->flip = o->s = 0;
    o->maintain();
    return o;
  }

  void init(int sz) {
    n = 0;
    null->s = 0;
    root = build(sz);
  }
};

vector<int> ans;
void print(Node* o) {
  if(o != null) {
    o->pushdown();
    print(o->ch[0]);
    ans.push_back(o->v);
    print(o->ch[1]);
  }
}

void debug(Node* o) {
  if(o != null) {
    o->pushdown();
    debug(o->ch[0]);
    printf("%d ", o->v-1);
    debug(o->ch[1]);
  }
}

SplaySequence ss;
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  ss.init(n+1); // 最前面有一个虚拟结点

  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b);
    Node *left, *mid, *right, *o;
    split(ss.root, a, left, o); // 如果没有虚拟结点，a将改成a-1，违反split的限制
    split(o, b-a+1, mid, right);
    mid->flip ^= 1;
    ss.root = merge(merge(left, right), mid);
  }

  print(ss.root);
  for(int i = 1; i < ans.size(); i++)
    printf("%d\n", ans[i]-1); // 节点编号减1才是本题的元素值

  return 0;
}
