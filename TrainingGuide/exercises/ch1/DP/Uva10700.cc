// Uva10700	Camel trading
// ³Â·æ
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long value_type;
const int MAXLEN = 36;
value_type MIN[MAXLEN][MAXLEN], MAX[MAXLEN][MAXLEN], PARSE[MAXLEN];
int N;
string exp;

inline bool isop(char c)
{
    return c == '+' || c == '*';
}

inline value_type eval(value_type left, value_type right, char op)
{
    return op == '+' ? left+right : left*right;
}

value_type parse(int i)
{
    value_type& ans = PARSE[i];
    if(ans != 0) return ans;
    ans = 0;
    while(!isdigit(exp[i])) i++;
    while(isdigit(exp[i])) ans = ans * 10 + exp[i++] - '0';
    return ans;
}

value_type minf(int i, int j)
{
    value_type& ans = MIN[i][j];    
    if(ans > 0) return ans;
    value_type left, right;
    
    int t;
    char c = 0;
    bool hasop = false;
    for(t = i; t < j; t++)
    {
        c = exp[t];
        if(isop(c))
        {
            hasop = true;
            left = minf(i, t);
            right = minf(t + 1, j);
            
            if(ans == 0) ans = eval(left, right, c);
            else ans = min(ans, eval(left, right, c));
        }
    }
    
    if(!hasop) ans = parse(i);
    
    return ans;
}

value_type maxf(int i, int j)
{
    value_type& ans = MAX[i][j];    
    if(ans > 0) return ans;
    value_type left, right;
    
    int t;
    char c = 0;
    bool hasop = false;
    for(t = i; t < j; t++)
    {
        c = exp[t];
        if(isop(c))
        {
            hasop = true;
            left = maxf(i, t);
            right = maxf(t + 1, j);
            ans = max(ans, eval(left, right, c));
        }
    }
    
    if(!hasop) ans = parse(i);
    
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>N;
    value_type min, max;
    while(N--)
    {
        cin>>exp;
        
        memset(MIN, 0, sizeof(MIN));
        memset(MAX, 0, sizeof(MAX));
        memset(PARSE, 0, sizeof(PARSE));
        
        min = minf(0, exp.size());
        max = maxf(0, exp.size());
        
        cout<<"The maximum and minimum are "<<max<<" and "<<min<<'.'<<endl;
    }
    return 0;
}