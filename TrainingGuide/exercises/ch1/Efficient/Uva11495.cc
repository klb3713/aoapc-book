// Uva11495	Bubbles and Buckets
// ³Â·æ
#include <cstdio>
#include <algorithm>

using namespace std;

inline bool isnum(char c)
{
    return c >= '0' && c <= '9';
}

inline int readint()
{
    char c = getchar();    
    while(!isnum(c)) c = getchar();
    
    int data = c - '0';
    while(isnum(c = getchar())) data = data * 10 + c - '0';
    
    return data;
}

int merge_sort(int *A, int l, int r, int *Temp)
{    
    int result = 0;
    if(l + 1 < r)
    {
        int m;
        m = l + (r-l)/2;
        result += merge_sort(A, l, m, Temp);
        result += merge_sort(A, m, r, Temp);
        
        int p = l, q = m, i = l;
        while(p < m || q < r)
        {
            if(q >= r || (p < m && A[p] < A[q])) Temp[i++] = A[p++];
            else
            {
                Temp[i++] = A[q++];
                result += (m - p) % 2;
            }
        }
        
        copy(Temp + l, Temp + r, A + l);
    }
    
    return result % 2;
}

const int MAXN = 100352;
int seq[MAXN];
int Temp[MAXN];
int main()
{
    int N;
    while(true)
    {
        N = readint();
        if(N == 0) break;
        for(int i = 0; i < N; i++) seq[i] = readint();
      
      int result = merge_sort(seq, 0, N, Temp);
      puts(result % 2 == 1 ? "Marcelo" : "Carlos");
   }
   
   return 0;
}
