#include<iostream>
using namespace std;
int k=0;
int f()
{
    return ++k;
}
int main(){
    int a,b;
    a=f();
    b=f();
    cout << "a="<< a<<",b="<<b<<endl;
    return 0;
}
