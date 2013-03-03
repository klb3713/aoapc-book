// Uva10391	Compound Words
// ³Â·æ
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    vector<string> words;
    set<string> results;
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(words));
    
    string left, right;
    for(vector<string>::iterator si = words.begin(); si != words.end(); si++)
    {        
        for(string::size_type j = 1; j < si->size(); j++)
        {
            left.assign(*si, 0, j);
            if(binary_search(words.begin(), words.end(), left))
            {
                right.assign(*si, j, si->size() - j);
                if(binary_search(words.begin(), words.end(), right))
                    results.insert(*si);
            }
        }
    }
    
    copy(results.begin(), results.end(), ostream_iterator<string>(cout, "\n"));
        
    return 0;
}
