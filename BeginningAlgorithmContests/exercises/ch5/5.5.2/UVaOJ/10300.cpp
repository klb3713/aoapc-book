#include<iostream>
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--)
    {
        int f,sum=0,s,n,d;
        cin >> f;
        while(f--) {cin >> s >> n >> d; sum+=s*d;}
        cout << sum<<endl;
    }
    return 0;
}
