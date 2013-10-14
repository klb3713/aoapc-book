#include<iostream>
#include<iomanip>
using namespace std;
int main(){
double t,s=0;
double average;
for(int i=1;i<=12;i++) {cin >> t; s+=t;}
average=s/12;
cout <<"$";
cout << setiosflags(ios::fixed)
     << setprecision(2) << average << endl;
return 0;
}
