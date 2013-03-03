// Uva10085	The most distant state
// 陈锋
#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;

struct State
{
    char grid[9];
    string steps;
    
    void read()
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                int temp;
                scanf("%d", &temp);
                grid[i * 3 + j] = temp;
            }
    }
    
    void output()
    {
        for(int i = 0; i < 3; i++)
            printf("%c %c %c\n", grid[3*i] + '0', grid[3*i+1] + '0', grid[3*i+2] + '0');
        puts(steps.c_str());
    }
};

const int MAXCODE = 362880;
bool visited[MAXCODE];
int fact[9];
void init_lookup_table()
{
    fact[0] = 1;
    for(int i = 1; i < 9; i++) fact[i] = fact[i-1] * i;
}

bool try_to_insert(const State& s)
{
    int code = 0;
    for(int i = 0; i < 9; i++)
    {
        int cnt = 0;
        for(int j = i+1; j < 9; j++)
            if(s.grid[j] < s.grid[i]) cnt++;
        code += fact[8-i] * cnt;
    }
    if(visited[code]) return false;
    return (visited[code] = true);
}

int main()
{
    int t = 1, T;
    char buf[16];
    deque<State> queue;
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    char MOVE[5] = {"UDLR"};
    scanf("%d", &T);
    init_lookup_table();
    
    while(t <= T)
    {
        printf("Puzzle #%d\n", t++);
        State init, end;

        gets(buf); // 空行
        init.read();
        fill_n(visited, MAXCODE, false);
        
        queue.push_back(init);
        try_to_insert(init);
        
        while(!queue.empty())
        {        
            int x, y, z;
            bool canMove = false;
            
            State s = queue.front();
            queue.pop_front();
            
            for(z = 0; z < 9; z++) if(!s.grid[z]) break;
            x = z/3, y = z%3;
            
            for(int d = 0; d < 4; d++)
            {
                int newx = x + dx[d], newy = y + dy[d], newz = newx*3 + newy;
                if(newx >= 0 && newx < 3 && newy >= 0 && newy < 3)
                {
                    State ns = s;
                    swap(ns.grid[z], ns.grid[newz]);
                    
                    if(try_to_insert(ns))
                    {
                        ns.steps.push_back(MOVE[d]);
                        canMove = true;
                        queue.push_back(ns);
                    }
                }
            }
            
            if(!canMove && s.steps.size() > end.steps.size())
                end = s;
        }
        
        end.output();
    }
    
    return 0;
}