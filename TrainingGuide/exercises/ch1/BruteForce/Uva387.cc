// Uva387	A Puzzling Problem
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 5, SIZE = 4;

inline bool isvalid(int x)
{
 return x >= 0 && x < SIZE;
}

struct Piece
{
 int Row;
 int Col;
 int CellCnt;
 char Shape[MAX][MAX];
 
 void readfrominput()
 {
  CellCnt = 0;
  scanf("%d%d\n", &Row, &Col);
  for(int i = 0; i < Row; i++) 
  {
   gets(Shape[i]);
   for(int j = 0; j < Col; j++) CellCnt += Shape[i][j] - '0';
  }
 }
 
 inline bool canarrange(char square[][MAX], int x, int y)
 {
  for(int i = 0; i < Row; i++)
  {
   if(!isvalid(x+i)) return false;
   for(int j = 0; j < Col; j++)
   {
    if(!isvalid(y+j)) return false;
    if(Shape[i][j] == '1' && square[x+i][y+j])
     return false;
   }
  }
  
  return true;
 }
 
 inline void arrange(char square[][MAX], int x, int y, int serial)
 {
  for(int i = 0; i < Row; i++)
   for(int j = 0; j < Col; j++)
    if(Shape[i][j] == '1')  square[x+i][y+j] = serial + '0';
 }
 
 inline void remove(char square[][MAX], int x, int y)
 {
  for(int i = 0; i < Row; i++)
   for(int j = 0; j < Col; j++)
    if(Shape[i][j] == '1') square[x+i][y+j] = 0;
 }
 
 void DebugPrint()
 {
  #ifdef DEBUG
  for(int i = 0; i < Row; i++)
  {
   puts(Shape[i]);
  }
  #endif
 }
};

bool dfs(char square[][MAX], Piece* pieces, int arranged, int usedCellsCnt, int PieceNum)
{
 if(arranged == PieceNum)
 {
  return usedCellsCnt == SIZE * SIZE;
 }
 
 Piece& currentPiece = pieces[arranged];
 for(int x = 0; x < SIZE; x++)
  for(int y = 0; y < SIZE; y++)
  {
   if(currentPiece.canarrange(square, x, y))
   {
    currentPiece.arrange(square, x, y, arranged + 1);
    if(dfs(square, pieces, arranged + 1, usedCellsCnt + currentPiece.CellCnt, PieceNum))
     return true;
    currentPiece.remove(square, x, y);
   }
  }
 
 return false;
}

int main()
{
 bool first = true;
 while(true)
 {
  char square[MAX][MAX];
  Piece pieces[MAX];
  int n;
  scanf("%d\n", &n);
  
  if(n == 0) break;
  
  memset(square, 0, sizeof(square));
  for(int i = 0; i < n; i++) 
  {
   pieces[i].readfrominput();
   pieces[i].DebugPrint();
  }
  
  if(first) first = false;
  else printf("\n");
  
  if(dfs(square, pieces, 0, 0, n))
   for(int i = 0; i < SIZE; i++)
    puts(square[i]);
  else
   puts("No solution possible");
 }
 
 return 0;
}
