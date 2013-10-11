#include<iostream>
#include<iomanip>
#include<cstdio>
#include<fstream>
using namespace std;
ifstream fin("stat.in");
ofstream fout("stat.out");
#define cin fin
#define cout fout
void task1()
{
	int max=0,n=0,a[100]={0},x;
	while(cin >> x)
	{
		if(++a[x]>max) max=a[x];
		if(x>n) n=x;
	}
	for(int i=0;i<=n;i++) if(a[i]==max) cout << i << " ";
	//for(int i=0,first=1;i<=n;i++) if(a[i]==max) {if(first) {cout << i;first=0;} else cout << " " << i;}
	return;
}
void task2()
{
	int max=0,n=-1,a[10010]={0}; //is hash?
	double x;
	while(cin >> x){
		if(++a[(int)floor(x*100)]>max) max=a[(int)floor(x*100+0.5)];
		if((int)floor(x*100)>n) n=(int)floor(x*100);
	}	
	for(int i=0;i<=n;i++) if(a[i]==max)
		//printf("%.2lf ",(double)i/100);
		cout << setiosflags(ios::fixed) << setprecision(2) << (double)i/100 << " ";
}
int main()
{
	//cout << "Choose module:\n1:N 2:.2R+\n";
	char ch;
	cin >> ch;
	if(ch=='1') task1();
	else task2();
	return 0;
}
