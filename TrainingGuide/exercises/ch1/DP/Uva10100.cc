// Uva10100	Longest Match
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

struct Word
{
    char* start;
    int len;
    
    inline bool operator==(const Word& rhs)
    {
        if(len != rhs.len) return false;
        for(int i = 0; i < len; i++)
            if(start[i] != rhs.start[i]) return false;
        
        return true;
    }
    
    void output()
    {
        for(int i = 0; i < len; i++) putchar(start[i]);
        putchar(' ');
    }
};

const int MAXLEN = 1024, MAXWORDS = 512;
char A[MAXLEN], B[MAXLEN];
Word AW[MAXWORDS], BW[MAXWORDS];
int D[MAXWORDS][MAXWORDS];

int extractWords(char* str, Word* pWord)
{
    int cnt = 0, wlen = 0;
    char prev = 0;
    while(*str)
    {
        char c = *str;
        if(isalnum(*str))
        {
            wlen++;
            if(!isalnum(prev)) pWord->start = str;
        }
        else if(isalnum(prev)) 
        {
            pWord->len = wlen;
            wlen = 0;
            pWord++;
            cnt++;
        }
        
        prev = c;
        str++;
    }
    
    if(isalnum(prev))
    {
        pWord->len = wlen;
        pWord++;
        cnt++;
    }
    
    return cnt;
}

int dp(int a, int b)
{
    int& ans = D[a][b];
    if(ans != -1) return ans;
    
    if(a == 0 || b == 0)
        return ans = 0;
    else if(AW[a-1] == BW[b-1])
        return ans = dp(a - 1, b - 1) + 1;
    else
        return ans = max(dp(a - 1, b), dp(a, b - 1));
}

int main()
{
    int a, b, s = 0;
    while(gets(A) != NULL && gets(B) != NULL)
    {
        memset(D, -1, sizeof(D));
        a = extractWords(A, AW);
        b = extractWords(B, BW);
        
        int l = dp(a, b);    
        
        printf("-. ", ++s);
        if(l > 0)
            printf("Length of longest match: %d\n", l);
        else
            puts("Blank!");
    }
    return 0;    
}
