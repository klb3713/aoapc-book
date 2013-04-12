// UVa11488 Hyper Prefix Sets
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int64;

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

template<int SIG_SIZE>
struct TrieNode
{
	int next[SIG_SIZE];
    int count;

	void init()
	{
		fill_n(next, SIG_SIZE, -1);
		count = 0;
	}
};

template<int SIG_SIZE, int MAXN>
struct Trie
{
    typedef TrieNode<SIG_SIZE> Node;
    vector<Node> nodes;
    int sz, ans, root;
    
    void init()
    {
        sz = 0; ans = -1;
		if(nodes.empty()) nodes.resize(MAXN);
        root = newNode();
    }
    
    int newNode()
    {
        if(sz == nodes.size())
		{
			printf("alloc -> sz = %d\n", sz);
            nodes.resize(sz * 2);
		}
		int ans = sz++;
		Node& n = nodes[ans];
		n.init();
		return ans;			 
    }
    
    void insert(const char *s) { insert(root, s, 0); }
    
    void insert(int o,  const char *s, int dep)
    {
        if(!(*s)) return;
        int c = *s - '0';
		int& no = nodes[o].next[c];
		if(no < 0) { no = newNode(); }
        ans = max(++(nodes[no].count) * (dep + 1), ans);
        insert(no, s + 1, dep + 1);
    }
};

const int maxn = 200 + 10;

Trie<2, 5000000> trie;
char buf[maxn];

void solve()
{
    int n = readint();
    trie.init();
    gets(buf);
    for(int i = 0; i < n; i++)
    {
        gets(buf);
        trie.insert(buf);
    }
    printf("%d\n", trie.ans);
}

int main()
{
    int T = readint();
    for(int t = 0; t < T; t++)
    {
        solve();
    }
    
    return 0;
}
