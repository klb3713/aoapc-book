// UVa 10368 Euclid's Game
// ³Â·æ
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef int DT;

bool canwin(DT a, DT b)
{
	if(a < b) swap(a, b);
	if(a % b == 0) return true;

	for(DT x = a % b; x < a; x += b)
		if(!canwin(x, b)) return true;
	
	return false;
}

int main()
{
	DT a, b;
	while(true)
	{
		cin>>a>>b;
		if(a == 0 && b == 0) break;
		
		bool win = canwin(a, b);
		cout<<(win ? "Stan" : "Ollie")<<" wins"<<endl;
	}

	return 0;
}
/* Ranking Submission Run Time Language Submission Date 
	586 	8455143 	0.012 	C++ 	2010-12-12 23:25:50 */