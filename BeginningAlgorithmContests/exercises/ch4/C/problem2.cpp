#include<iostream>
using namespace std;

int* f()
{
    int a=3;
    cout << a<< endl;
    return &a;
}

int main()
{
    int* b=f();
    cout << *b << endl;
    return 0;
}
