// Uva10827 Maximum sum on a torus
// ³Â·æ
#include<stdio.h>

#define MAXN 80
#define MAX 100*75*75
#define MIN -100*75*75

int Case,n;
int a[MAXN][MAXN];
int f[MAXN][MAXN][MAXN],g[MAXN][MAXN][MAXN];
int w[MAXN][MAXN]={0};
int ans;

int max(int a,int b)
{
 return a>b?a:b;
}

int min(int a,int b)
{
 return a>b?b:a;
}

void Init()
{
 int i,j;
 scanf("%d",&n);
 for (i=0;i<n;i++)
  for (j=0;j<n;j++)
   scanf("%d",&a[i][j]);
}

void Make_graph_a(int Head)
{
 if (Head==0) return;
 
 int b[MAXN];
 int i,j;

 for (j=0;j<n;j++)
  b[j]=a[0][j];

 for (i=0;i<n-1;i++)
  for (j=0;j<n;j++)
   a[i][j]=a[i+1][j];

 for (j=0;j<n;j++)
  a[n-1][j]=b[j];
}

void Make_graph_f(int Head)
{
 int i,j;
 for (i=0;i<n;i++)
  for (j=0;j<n;j++)
  {
   f[i+1][i+1][(j-Head+n)%n+1]=a[i][j];
   g[i+1][i+1][(j-Head+n)%n+1]=a[i][j];
   ans=max(ans,a[i][j]);
  }
}

void Prepared_DP()
{
 int i,j;
 for (j=1;j<=n;j++)
  for (i=1;i<=n;i++)
   w[i][j]=w[i-1][j]+f[i][i][j];
}

void DP()
{
 int len,i,j,k,tmp;
 int fans,gans,sum;

 for (len=2;len<=n;len++)
  for (i=1;i<=n-len+1;i++)
  {
   j=i+len-1;
   fans=MIN; gans=MAX; sum=0;
   for (k=1;k<=n;k++)
   {
    tmp=w[j][k]-w[i-1][k];
    sum+=tmp;
    f[i][j][k]=max(tmp,f[i][j][k-1]+tmp);
    g[i][j][k]=min(tmp,g[i][j][k-1]+tmp);
    fans=max(fans,f[i][j][k]);
    gans=min(gans,g[i][j][k]);
   }
   ans=max(ans,fans);
   ans=max(ans,sum-gans);
  }
}

int main()
{
 int h,z;

 scanf("%d",&Case);
 while (Case--)
 {
  Init();
  ans=a[0][0];
  for (z=0;z<n;z++)
  {
   Make_graph_a(z);
   Make_graph_f(h);
   Prepared_DP();
   DP();
  }
  printf("%d\n",ans);
 }
 return 0;
}
