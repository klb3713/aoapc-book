#include<fstream>
#include<cmath>
using namespace std;
ifstream fin("base2.in");
ofstream fout("base2.out");
int main()
{
 int b,s[100],top=0,ans=0;
 char c;
 fin >> b;
 while(fin>>c) s[++top]=c-'0';
 int i=0;
 while(top) ans+=s[top--]*pow(b,i++);
 fout << ans;
 return 0;
}
