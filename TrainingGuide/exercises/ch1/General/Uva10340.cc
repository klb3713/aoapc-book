// Uva10340	All in All
// ³Â·æ
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string s, t;
    while(cin>>s>>t)
    {
        bool found = true;
        string::size_type pos = -1;
        for(string::iterator ps = s.begin(); ps != s.end(); ps++)
        {
            pos = t.find(*ps, pos + 1);
            if(pos == string::npos)
            {
                found = false;
                break;
            }
        }
        cout<<(found ? "Yes" : "No")<<endl;
    }
    return 0;
}
