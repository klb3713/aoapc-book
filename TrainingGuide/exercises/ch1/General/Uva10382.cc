// Uva10382	Watering Grass
// ³Â·æ
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
const int MAXN = 10240;
const double EPS = 1e-11;

struct Range
{
    double a;
    double b;
    
    inline bool operator< (const Range& rhs) const
    {
        return a < rhs.a || (a == rhs.a && b < rhs.b);
    }
};

int main()
{
    int n, l, w;
    double length, weight;
    vector<Range> ranges;
    ranges.reserve(MAXN);
    
    while(scanf("%d%d%d", &n, &l, &w) == 3)
    {
        length = (double)l;
        weight = w / 2.0;
        
        ranges.clear();
        for(int i = 0; i < n; i++)
        {
            int position, radius;
            double xw;
            Range range;
            
            scanf("%d%d", &position, &radius);
            if(radius * 2 <= w) continue;
                        
            xw = sqrt((double)radius * radius - weight * weight);
            
            range.a = position - xw;
            if(range.a > length + EPS) continue;
            else if(range.a - EPS < 0.0) range.a = 0.0;
            
            range.b = position + xw;
            ranges.push_back(range);
        }
        
        sort(ranges.begin(), ranges.end());
        
        int minCover = 0;        
        double start = 0.0, end = 0.0;
        for(vector<Range>::iterator pr = ranges.begin(); pr != ranges.end(); )
        {
            start = end;
            if(pr->a > start + EPS)
            {
                minCover = -1;
                break;
            }
            
            minCover++;
            
            while(pr != ranges.end() && pr->a <= start)
            {
                if(pr->b - end > EPS) end = pr->b;
                pr++;
            }
            
            if(end - length > EPS) break;
        }
        if(end + EPS < length) minCover = -1;
        
        printf("%d\n", minCover);
    }
    
    return 0;
}