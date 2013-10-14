#include<iostream>
#include<cstring>
using namespace std;
int main()
{
 int n;
 int dna[10];
 int cell[42];
 int tom[42];
 cin >> n;
 for(int i=1;i<=n;i++)
 {
  memset(dna,0,sizeof(dna));
  memset(cell,0,sizeof(cell));
  memset(tom,0,sizeof(tom));
  cell[20]=1;
  tom[20]=1;
  for(int j=0;j<10;j++) cin >> dna[j];
  for(int day=1;day<=50;day++){
   for(int i=1;i<=40;i++) {
    cell[i]=tom[i];
    switch(tom[i]){
    case 0:cout << " "; break;
    case 1:cout << "."; break;
    case 2:cout << "x"; break;
    case 3:cout << "W"; break;
    }
   }
   cout << endl;
   for(int i=1;i<=40;i++) tom[i]=dna[cell[i-1]+cell[i]+cell[i+1]];
  }
  if(i<n) cout << endl;
 }
 return 0;
}

/*
sample input:
1
0 1 2 0 1 3 3 2 3 0

sample output:
(false answer intended to help you read:)
bbbbbbbbbbbbbbbbbbb.bbbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbbb...bbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbb.xbx.bbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbb.bb.bb.bbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbb.........bbbbbbbbbbbbbbbb
bbbbbbbbbbbbbb.xbbbbbbbx.bbbbbbbbbbbbbbb
bbbbbbbbbbbbb.bbxbbbbbxbb.bbbbbbbbbbbbbb
bbbbbbbbbbbb...xxxbbbxxx...bbbbbbbbbbbbb
bbbbbbbbbbb.xb.WW.xbx.WW.bx.bbbbbbbbbbbb
bbbbbbbbbb.bbb.xxWb.bWxx.bbb.bbbbbbbbbbb
bbbbbbbbb...b.bWxW...WxWb.b...bbbbbbbbbb
bbbbbbbb.xbxx..WWWWbWWWW..xxbx.bbbbbbbbb
bbbbbbb.bb..W.WxbbWWWbbxW.W..bb.bbbbbbbb
bbbbbb....xWWxWWxbWbWbxWWxWWx....bbbbbbb
bbbbb.xbb.WWWWWWWWbWbWWWWWWWW.bbx.bbbbbb
bbbb.bbx..xbbbbbbWWbWWbbbbbbx..xbb.bbbbb
bbb...xb..bxbbbbbWWWWWbbbbbxb..bx...bbbb
bb.xb.bbxxbxxbbbbWbbbWbbbbxxbxxbb.bx.bbb
b.bbb..x.....xbbbbbbbbbbbx.....x..bbb.bb
...b.x...bbb.bxbbbbbbbbbxb.bbb...x.b...b
xbxxb..bx.b..bxxbbbbbbbxxb..b.xb..bxxbx.
x...bxxbbbxxxb..xbbbbbx..bxxxbbbxxb...bb
b.bxb..xbx.W.bx.bxbbbxb.xb.W.xbx..bxbx.b
..bxbx.b.bWW.bbbbxxbxxbbbb.WWb.b.xbx.bb.
xxbx.bbx..Wx..bbx.....xbb..xW..xbb.bb...
...bb.xb.WWW.x.xb.bbb.bx.x.WWW.bx....xbx
xbx..bbb.xbxW.Wbb..b..bbW.Wxbx.bb.bb.b.x
x.b.x.b.bb.WWx.b.xxxxx.b.xWW.bb......xbb
bbxb.bx....xWWbxbWWWWWbxbWWx...xbbbb.bxb
bxxb.bb.bb.WWWWxWWbbbWWxWWWW.b.bxbb..bxx
x..b.......xbbWWWWbbbWWWWbbx.x.bxx.xxb..
b.xxxbbbbb.bxbWbbWbbbWbbWbxbW.bb.WWW.bxx
.bWW.xbbb..bxWbbbbbbbbbbbWxW.....xbx.b..
..WxWbxb.xxbWWbbbbbbbbbbbWWWWbbb.b.bbxxx
xWWWWWxbbW.WWWbbbbbbbbbbbWbbWbb..x..x.W.
WWbbbWWxb.xxbWbbbbbbbbbbbbbbbb.x.....WW.
WWbbbWWWbbW.Wbbbbbbbbbbbbbbbb.b..bbbWxx.
WWbbbWbWbb.x.bbbbbbbbbbbbbbb..xxx.bbWxWb
WWbbbbWbb.b.b.bbbbbbbbbbbbb.x.WWWb.bWWWb
WWbbbbbb..x.x..bbbbbbbbbbb.b.WxbW...WbWb
WWbbbbb.x..W..x.bbbbbbbbb..x.WWW.WbW.Wbb
WWbbbb.b..WWW..b.bbbbbbb.x..Wxbxx.W.x.bb
WWbbb..xxWxbxWxx..bbbbb.b..WWW..WWWW.b.b
WWbb.x.WxxW.WxxW.x.bbb..xxWxbxWWxbbx.x..
WWb.b.WWxxWxWxxWW.b.b.x.WxxW.WWWWxxbW..x
WW..x.xWxxxWxxxWx.x.xb.WWxxWxxbbWx.W.W.b
WxW..WWxxWxxxWxxWW.Wbb.xWxxxx.xbWWWWxW..
WWWWWxWxxxxWxxxxWxx.b.bWxxWWWWbWWbbWWWWx
WbbbWWxxWWxxxWWxxxWbx..WxxWbbWWWWbbWbbWW
bbbbWWxxWWxWxWWxWxWWb.WWxxWbbWbbWbbbbbWW

' ' instead of 'b'(real answer):
                   .
                  ...
                 .x x.
                .  .  .
               .........
              .x       x.
             .  x     x  .
            ...xxx   xxx...
           .x .WW.x x.WW. x.
          .   .xxW . Wxx.   .
         ... . WxW...WxW . ...
        .x xx..WWWW WWWW..xx x.
       .  ..W.Wx  WWW  xW.W..  .
      ....xWWxWWx W W xWWxWWx....
     .x  .WWWWWWWW W WWWWWWWW.  x.
    .  x..x      WW WW      x..x  .
   ...x .. x     WWWWW     x .. x...
  .x .  xx xx    W   W    xx xx  . x.
 .   ..x.....x           x.....x..   .
... .x...   . x         x .   ...x. ...
x xx .. x. .. xx       xx .. .x .. xx x.
x... xx   xxx ..x     x.. xxx   xx ...
 . x ..x x.W. x. x   x .x .W.x x.. x x.
.. x x. . WW.    xx xx    .WW . .x x.  .
xx x.  x..Wx..  x.....x  ..xW..x  .  ...
...  .x .WWW.x.x .   . x.x.WWW. x....x x
x x..   .x xW.W  .. ..  W.Wx x.  .  . .x
x. .x. .  .WWx. .xxxxx. .xWW.  ......x
  x . x....xWW x WWWWW x WWx...x    . x
 xx .  .  .WWWWxWW   WWxWWWW. . x  .. xx
x.. .......x  WWWW   WWWW  x.x. xx.xx ..
 .xxx     . x W  W   W  W x W.  .WWW. xx
. WW.x   .. xW           WxW.....x x. ..
..WxW x .xx WW           WWWW   . .  xxx
xWWWWWx  W.WWW           W  W  ..x..x.W.
WW   WWx .xx W                .x.....WW.
WW   WWW  W.W                . ..   Wxx.
WW   W W  .x.               ..xxx.  WxW
WW    W  . . .             .x.WWW . WWW
WW      ..x.x..           . .Wx W...W W
WW     .x..W..x.         ..x.WWW.W W.W
WW    . ..WWW.. .       .x..Wx xx.W.x.
WW   ..xxWx xWxx..     . ..WWW..WWWW. .
WW  .x.WxxW.WxxW.x.   ..xxWx xWWx  x.x..
WW . .WWxxWxWxxWW. . .x.WxxW.WWWWxx W..x
WW..x.xWxxxWxxxWx.x.x .WWxxWxx  Wx.W.W.
WxW..WWxxWxxxWxxWW.W  .xWxxxx.x WWWWxW..
WWWWWxWxxxxWxxxxWxx. . WxxWWWW WW  WWWWx
W   WWxxWWxxxWWxxxW x..WxxW  WWWW  W  WW
    WWxxWWxWxWWxWxWW .WWxxW  W  W     WW
*/

