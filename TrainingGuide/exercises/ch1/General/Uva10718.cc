// UVa10718 Bit Mask
// 陈锋
#include<iostream>
using namespace std;

unsigned int n,l,u,ll;

int main()
{
    unsigned int j;

    while (cin>>n>>l>>u)
    {
        ll = 0;

        for (j = 31; j<32; j--)
        {
            //  ((n的第j+1位为0 或 (l的第j+1位为1 并且 ll小于l)) && (填1小于u))
            if (((n|(1<<j))!=n || ((l|(1<<j))==l && ll < l) ) && (ll | (1<<j))<=u) ll = ll | (1<<j);//填1
            else
                if (ll > l) ll=ll;
        }
        cout<<ll<<endl;
    }

    return 0;
}
