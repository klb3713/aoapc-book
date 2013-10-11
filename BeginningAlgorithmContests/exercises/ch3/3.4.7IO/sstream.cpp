#include<iostream>
#include<sstream>
using namespace std;
int main()
{
 char s[1000];
 cin.getline(s,1000,'\n');
 stringstream k(s);
 int a,b;
 k >> a >> b;
 cout << a << endl;
 cout << a+b << endl;
 return 0;
}
