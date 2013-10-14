#include<iostream>
using namespace std;
int k=4;
int f(){return (k=k*3);}
int g(){return (k=k-2);}
int h(){return (k=k/5);}
int main()
{
    int a,b;
    a=(f()+g())+h();
    b=f()+(g()+h());
    cout <<a <<" "<< b<<endl;
    return 0;
}
