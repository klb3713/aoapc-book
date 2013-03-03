// Uva10400	Game Show Math
// 陈锋
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int readint()
{
    int num;
    scanf("%d", &num);
    return num;
}

const int MAXR = 32000, MAXP = 100, OPCNT = 4;
int Seq[MAXP], D[MAXP+1][2 * MAXR];
const char OP[] = "+-*/";

inline int getleft(char op, int right, int target)
{
    switch(op)
    {
        case '+': return target - right;
        case '-': return target + right;
        case '*': return target / right;
        case '/': return target * right;
        default: return 1 / 0; // Assert
    }
}

inline int eval(char op, int left, int right)
{
    switch(op)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default: return 1 / 0; // Assert
    }
}

// i是当前数列的长度
bool dfs(int i, int target, vector<char>& exp)
{
    int& ans = D[i][target + MAXR];
    if(ans != -1) return ans == 1;
    
    if(i == 1) 
    {
        ans = Seq[0] == target ? 1 : 0;
        return ans == 1;
    }
    
    ans = 0;
    for(int j = 0; j < OPCNT; j++)
    {
        int left = getleft(OP[j], Seq[i-1], target);
        if(abs(left) < MAXR && eval(OP[j], left, Seq[i-1]) == target)
        {
            exp.push_back(OP[j]);
            if(dfs(i-1, left, exp))
            {
                ans = 1;
                break;
            }
            exp.pop_back();
        }
    }
    
    return ans == 1;
}

int main()
{
    int i, N, P, Target;
    vector<char> ops;
    ops.reserve(MAXP);
    N = readint();
    while(N--)
    {
        P = readint();
        ops.clear();
        memset(D, -1, sizeof(D));
        for(i = 0; i < P; i++) Seq[i] = readint();
        Target = readint();
        
        if(dfs(P, Target, ops))
        {
            printf("%d", Seq[0]);
            for(i = 1; i < P; i++)
                printf("%c%d", ops[ops.size() - i], Seq[i]);
            printf("=%d\n", Target);
        }
        else
            puts("NO EXPRESSION");
    }
    return 0;
}

// Ranking	Submission	Run Time	Language	Submission Date
// 137	    8397591	    0.360	    C++	        2010-11-15 07:35:48