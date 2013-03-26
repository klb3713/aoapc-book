// UVa11987 Almost Union-Find
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long int64;

struct ListNode
{
    int num;
    ListNode* next; 
    ListNode* prev; 
    ListNode* parent; 
    ListNode* tail;
};

const int maxn = 100000;
ListNode nodes[maxn];
int n, m;

void insert(ListNode *p, ListNode* root)
{
    p->parent = root;
    p->prev = root->tail;
    root->tail->next = p;
    p->next = NULL;
    root->tail = p;
}

ListNode* findRoot(int x)
{
    ListNode *px = nodes + x;
    ListNode *root = px->parent;
    while(root != root->parent)
       px->parent = (root = root->parent);
    return root;        
}

// Union the sets containing a and b;
void uni_set(int a, int b)
{
    // printf("uni_set %d %d\n", a, b);
    ListNode *aRoot = findRoot(a), *bRoot = findRoot(b);
    if(aRoot == bRoot) return;
    
    bRoot->tail->next = aRoot;
    aRoot->prev = bRoot->tail;
    bRoot->tail = aRoot->tail;    
    
    ListNode* cur = aRoot;
    while(cur)
    {
        cur->parent = bRoot;
        cur = cur->next;
    }    
}

// Move a to the set containing b. 2 a b
void move_set(int a, int b)
{
    // printf("move_set %d %d\n", a, b);
    ListNode *p = nodes + a, *aRoot = findRoot(a), *bRoot = findRoot(b);
    if(aRoot == bRoot) return;
    
    // 如果a就是代表元
    if(p == aRoot)
    {
        ListNode *cur = p->next, *first = cur;
        if(cur)
        {
            cur->prev = NULL;
            cur->tail = aRoot->tail;
        }
        
        while(cur)
        {
            cur->parent = first;
            cur=cur->next;
        }
        
        insert(p, bRoot);        
        return;
    }
    
    // 如果a就是tail呢
    if(p == aRoot->tail)
        aRoot->tail = p->prev;
    p->prev->next = p->next;
    if(p->next)
        p->next->prev = p->prev;
    
    insert(p, bRoot);
}

void query_set(int p)
{
    // printf("query_set %d\n", p);    
    ListNode *cur = findRoot(p);
    int64 num = 0, sum = 0;
    while(cur)
    {
        num++;
        sum += cur->num;
        cur = cur->next;
    }
    printf("%lld %lld\n", num, sum);
}

void dbg_print()
{
   set<int> vis;
   for(int i = 1; i <= n; i++) 
   {
        if(vis.count(i)) continue;
        printf("{");
        
        ListNode *cur = findRoot(i);
        while(cur)
        {
            printf("%d ", cur->num);
            vis.insert(cur->num);
            cur=cur->next;
        }
        
        printf("}, ");
   }
   puts("");
}

int main()
{
    while(scanf("%d%d", &n, &m) == 2)
    {
        ListNode *cur = nodes + 1;
        for(int i = 0; i < n; i++)
        {
            cur->num = i + 1;
            cur->next = NULL;
            cur->parent = cur;
            cur->tail = cur;
            cur++;
        }
        
        for(int i = 0; i < m; i++)
        {
            // dbg_print();
            int cid, p, q;
            scanf("%d%d", &cid, &p);
            if(cid != 3) scanf("%d", &q);
            
            switch(cid)
            {
                case 1:
                    uni_set(p, q);
                    break;
                case 2:
                    move_set(p, q);
                    break;
                case 3:
                    query_set(p);
                    break;
            }
        }
    }
}
