// Uva10125	Sumsets
// ³Â·æ
#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

int readint()
{
    int num;
    scanf("%d", &num);
    return num;
}

int main()
{
    vector<int> S;
    greater<int> comp;
    S.reserve(1024);
    while(true)
    {
        int n = readint();
        if(n == 0) break;
        
        S.clear();
        for(int i = 0; i < n; i++) S.push_back(readint());
        
        sort(S.begin(), S.end(), comp);
        
        vector<int>::iterator pd, pc, pb;
        int maxd = 0;
        bool found = false;
        for(pd = S.begin(); pd != S.end(); pd++)
        {
            for(pc = S.begin(); pc != S.end(); pc++)
            {
                if(*pc == *pd) continue;
            
                pb = pc;
                while(pb != S.end() && *pb == *pc) pb++;
                
                for(; pb != S.end(); pb++)
                {
                    if(*pb == *pd) continue;
                
                    int a = *pd - *pc - *pb;
                    if(a >= *pb || a == *pd) continue;
                    
                    if(binary_search(pb, S.end(), a, comp))
                    {
                        found = true;
                        maxd = *pd;
                        goto RESULT;
                    }
                }
            }
        }
        
    RESULT:
        if(found) printf("%d\n", maxd);
        else puts("no solution");
    }
    return 0;
}