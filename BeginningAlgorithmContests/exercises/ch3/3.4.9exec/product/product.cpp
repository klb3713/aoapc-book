#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
using namespace std;
int main()
{
	int a=0;
	long long ans=1;
	char c;
	while((c=getchar())!=EOF) {
	if(isdigit(c)) a=a*10+c-'0';
	else if(c==' ') {ans*=a; a=0;}
	if(ans==0) break;
	}
	ans*=a;
	printf("%3lld\n",ans%1000);
	return 0;
}
