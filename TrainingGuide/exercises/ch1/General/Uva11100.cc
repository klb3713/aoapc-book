// Uva11100 The Trip, 2007
// ³Â·æ
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>

inline int readint()
{
    int num;
    scanf("%d", &num);
    return num;
}

using namespace std;

const int MAXN = 10240;

int main()
{
    vector<int> pieces;    
    vector< vector<int> > sln;
    sln.reserve(MAXN);
    pieces.reserve(MAXN);
    
    bool flag = false;
    while(true)
    {
        int i, n, k;
        if((n = readint()) == 0 ) break;
        
        sln.clear();
        pieces.clear();
        k = 0;
        
        for(i = 0; i < n; i++) pieces.push_back(readint());
        sort(pieces.begin(), pieces.end(), greater<int>());
        
        vector< vector<int> >::iterator st, minst;
        vector<int>::iterator it;
        
        int prev, cnt;
        prev = -1, cnt = 0;
        for(it = pieces.begin(); it != pieces.end(); it++)
        {
            if(*it != prev)
            {
                cnt = 1;
                prev = *it;
            }
            else
            {
                cnt++;
                if(cnt > k) k = cnt;
            }
        }
        
        sln.resize(k);
        for(it = pieces.begin(); it != pieces.end(); it++)
        {
            minst = sln.end();
            for(st = sln.begin(); st != sln.end(); st++)
            {
                if(st->empty() || st->back() > *it )
                {
                    if(minst == sln.end() || st->size() < minst->size()) minst = st;
                }
            }
            
            if(minst == sln.end())
            {
                sln.resize(sln.size() + 1);
                sln.back().push_back(*it);
            }
            else
                minst->push_back(*it);
        }
        
        if(flag) putchar('\n');
        else flag = true;
        
        printf("%d\n", sln.size());
        for(st = sln.begin(); st != sln.end(); st++)
        {
            it = st->begin();
            printf("%d", *it); it++;
            for(; it != st->end(); it++) printf(" %d", *it);
            putchar('\n');
        }
    }
    return 0;
}
