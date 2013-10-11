//word
#include<iostream>
using namespace std;
int main()
{
	int n=0,sum=0;
	string s;
	freopen("word.in","r",stdin);
	freopen("word.out","w",stdout);
	while(cin >> s) {sum+=s.length(); n++;}
	cout << (float)sum/n << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
