#include<iostream>
#include<iomanip>
#include<cstdio>
#include<fstream>
using namespace std;
ofstream fout("buf.out");
int main()
{
 string s;
 freopen("string.in","r",stdin);
 freopen("time","a",stdout);
 while(cin >> s) fout << s;
 cout <<"cincout:"
       <<setiosflags(ios::fixed) << setprecision(3) << (double)clock()/CLOCKS_PER_SEC<<"s\n";
 return 0;
}
