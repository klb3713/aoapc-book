// UVa1264(LA4847) Binary Search Tree
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

struct Node
{
    Node *left, *right;
    int count, value;
    int64 dp;
    
    int lcnt(){ 
        if(left) return left->count; 
        return 0;
    }
    
    int rcnt(){ 
        if(right) return right->count;
        return 0;
    }
};

const int MAXN = 20 + 4, MOD = 9999991;
Node nodes[MAXN], *root;
int sz;
int64 c[MAXN][MAXN];

void C()  
{  
    int i,j;  
    c[0][0]=1;  
    for(i=1;i<MAXN;i++)    //自定义  
        for(j=0;j<=i;j++)  
            c[i][j]=(j==0)? c[i-1][j] : c[i-1][j]+c[i-1][j-1];    //公式  
}  

Node* newNode(int v)
{
    Node *p = &(nodes[sz++]);
    p->value = v;
    p->dp = 1;
    p->count = 1;
    return p;
}

void insert(int x)
{
    if(!root) {
        root = newNode(x);
        return;
    }
    
    Node *cur = root;
    while(true)
    {
        assert(cur != NULL);
        if(x < cur->value)
        {
            if(cur->left == NULL) { cur->left = newNode(x); return; }
            else cur = cur->left;
        }
        else
        {
            if(cur->right == NULL) { cur->right = newNode(x); return; }
            else cur = cur->right;
        }
    }
}

void dfs(Node* p)
{
    if(!(p->left) && !(p->right)) return;
    if(p->left) dfs(p->left);
    if(p->right) dfs(p->right);
    
    p->count = p->lcnt() + p->rcnt() + 1;
    if(p->left && p->right)
    {  
        int64 cc = c[p->count-1][p->rcnt()];
        p->dp = cc * p->left->dp * p->right->dp % MOD;
    }else if(p->right)  
    {  
        p->dp = p->right->dp;  
    }else  
    {  
        p->dp = p->left->dp;
    }  
}

void solve()
{
    root = NULL;
    sz = 0;
    memset(nodes, 0, sizeof(nodes));
    
    int N = readint();
    for(int i = 0; i < N; i++)
        insert(readint());
    
    dfs(root);
    printf("%lld\n", root->dp);
}

int main()
{
    C();
    int T = readint();    
    for(int i = 0; i < T; i++)
        solve();
    
    return 0;
}
