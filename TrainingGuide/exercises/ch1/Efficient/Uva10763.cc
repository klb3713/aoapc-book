// Uva10763	Foreign Exchange
// ³Â·æ
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Candidate
{
 int source;
 int target;
 bool match;
 
 inline bool operator<(const Candidate& rhs) const
 {
  return source < rhs.source || (source == rhs.source && target < rhs.target);
 }
};

typedef vector<Candidate>::iterator CandIter;

int main()
{
 vector<Candidate> cands;
 cands.reserve(500000);
 
 while(true)
 {
  int i, n;
  Candidate cand;
  bool hasSolution = true;
  scanf("%d", &n);
  if(n == 0) break;
  
  cands.clear();
  cand.match = false;
  for(i = 0; i < n; i++)
  {
   scanf("%d%d", &(cand.source), &(cand. target));
   cands.push_back(cand);   
  }
  sort(cands.begin(), cands.end());
  
  for(CandIter cur = cands.begin(); cur != cands.end(); cur++)
  {
   if(cur->match) continue;
  
   Candidate matchCand;
   pair<CandIter, CandIter> range;
   
   matchCand.source = cur->target;
   matchCand.target = cur->source;   
   range = equal_range(cur + 1, cands.end(), matchCand);
   
   for(CandIter mIter = range.first; mIter != range.second; mIter++)
   {
    if(!mIter->match 
     && mIter->source == cur->target && mIter->target == cur->source)
    {
     cur->match = true;
     mIter->match = true;
     break;
    }
   }
   
   if(!cur->match)
   {
    hasSolution = false;
    break;
   }
  }

  puts(hasSolution ? "YES" : "NO");
 }
 
 return 0;
}
