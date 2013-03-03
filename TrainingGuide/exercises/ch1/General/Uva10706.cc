// Uva10706	Number Sequence
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXK = 31268;
int S[MAXK], G[MAXK];
int main()
{
 char buf[16];
 
 S[1] = 1;
 G[1] = 1;
 for(int i = 2; i < MAXK; i++)
 {
  sprintf(buf, "%d", i);
  S[i] = S[i-1] + strlen(buf);
  G[i] = G[i-1] + S[i];
 }
 
 int t;
 scanf("%d", &t);
 while(t--)
 {
  int i, k, *pSK, posInSK, n;
  scanf("%d", &i);
  pSK = lower_bound(G + 1, G + MAXK, i);
  k = pSK - G;
  posInSK = i - *(pSK - 1); // position in SK
  n = lower_bound(S + 1, S + MAXK, posInSK) - S; // number contains pos
  sprintf(buf, " %d", n);
  printf("%c\n", buf[posInSK - S[n-1]]);
 }
 
 return 0;
}