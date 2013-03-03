// Uva10051	Tower of Cubes
// 陈锋
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int FACENUM = 6, MAXN = 512;

struct cube
{
    int colors[FACENUM]; // front, back, left, right, top 以及bottom 的color
    inline void read()
    {
        for(int i = 0; i < FACENUM; i++) 
            scanf("%d", colors + i);
    }
};

cube cubes[MAXN];
int N, D[MAXN][FACENUM], opposite[FACENUM] = {1, 0, 3, 2, 5, 4};
char facestring[FACENUM][8] = {"front", "back", "left", "right", "top", "bottom"};

inline bool match(int i, int iFace, int j, int jFace)
{
    return cubes[i].colors[opposite[iFace]] == cubes[j].colors[jFace];
}

int dp(int i, int face)
{
    int& ans = D[i][face];
    if(ans != 0) return ans;
    
    ans = 1;
    for(int j = i + 1; j < N; j++)
        for(int jf = 0; jf < FACENUM; jf++)
            if(match(i, face, j, jf))
                ans = max(ans, 1 + dp(j, jf));
    
    return ans;
}

void print_ans(int i, int face)
{
    printf("%d %s\n", i + 1, facestring[face]);
    int ans = D[i][face];
    
    for(int j = i + 1; j < N; j++)
    {
        int jf;
        for(jf = 0; jf < FACENUM; jf++)
        {
            if(D[j][jf] == ans - 1 && match(i, face, j, jf))
            {
                print_ans(j, jf);
                break;
            }
        }
        
        if(jf < FACENUM) break;
    }
}

int main()
{
    int c = 0;
    bool first = true;
    while(true)
    {
        int i, f;
        scanf("%d", &N);
        if(N == 0) break;
        
        for(i = 0; i < N; i++) cubes[i].read();
        memset(D, 0, sizeof(D));
        
        int ans = 0;
        for(i = 0; i < N; i++)
            for(f = 0; f < FACENUM; f++)
                ans = max(ans, dp(i, f));
        
        if(first) first = false;
        else puts("");
        printf("Case #%d\n%d\n", ++c, ans);
        
        for(i = 0; i < N; i++)
        {
            for(f = 0; f < FACENUM; f++)
            {
                if(D[i][f] == ans)
                {
                    print_ans(i, f);
                    break;
                }
            }
            
            if(f < FACENUM) break;
        }
    }
    return 0;
}