// UVa10895 Matrix Transpose
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef pair<int,int> intPair;
struct matrix
{
    int m, n;
    map<intPair, int> values;
    
    void setValue(int r, int c, int value)
    {
        const intPair& pos = make_pair(r, c);
        values[pos] = value;
    }    
    
    void init(int m, int n)
    {
        this->m = m;
        this->n = n;
        values.clear();
    }
  
    matrix transpose()
    {
        matrix ans;
        ans.init(n, m);
        for(map<intPair, int>::iterator it = values.begin(); it != values.end(); it++)
            ans.setValue(it->first.second, it->first.first, it->second);
        return ans;
    }
  
    void print_cols(const vector<int>& cols, const vector<int>& vs)
    {
        // 新的一行
        printf("%d", cols.size());
        for(int i = 0; i < cols.size(); i++)
            printf(" %d", cols[i]);
        puts("");
        
        for(int i = 0; i < vs.size(); i++)
        {
            if(i) printf(" ");
            printf("%d", vs[i]);
        }
        puts("");
    }
    
    void output()
    {
        printf("%d %d\n", m, n);
        map<intPair, int>::iterator it;
        vector<int> cols, vs;
        int lastR = values.begin()->first.first;
        
        for(int i = 1; i < lastR; i++)
            puts("0\n");
        
        for(it = values.begin(); it != values.end(); it++)
        {
            if(it->first.first != lastR)
            {              
                print_cols(cols, vs);
                cols.clear();
                vs.clear();

                for(int i = lastR + 1; i < it->first.first; i++)
                    puts("0\n");
            }
            
            lastR = it->first.first;
            cols.push_back(it->first.second);
            vs.push_back(it->second);
        }
        
        print_cols(cols, vs);
        for(int i = lastR + 1; i <= m; i++)
            puts("0\n");
    }
};

int main()
{
    matrix mat;
    while(true)
    {
        int m, n;
        if(scanf("%d%d", &m, &n) != 2) break;
        
        mat.init(m, n);
        
        int r, c, v;
        
        vector<int> cols;
        for(int i = 1; i <= m; i++)
        {   
            cols.clear();
            scanf("%d", &r);
            for(int j = 0; j < r; j++)
            {
                scanf("%d", &c);
                cols.push_back(c);
            }
            
            for(int j = 0; j < r; j++)
            {
                scanf("%d", &v);
                mat.setValue(i, cols[j], v);
            }
        }
        
        matrix ans = mat.transpose();
        ans.output();
    }
    
    return 0;
}
