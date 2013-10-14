#include<iostream>
#include<cstdio>
#include<cassert>
using namespace std;
//#define db const double
typedef const double db;
void solve(db a,db b, db c,db d, db e,db f,double &x,double &y)
{
   assert(a*e-b*d!=0.);
   //cout << a << b<<c<<d<<e<<f << endl;
   x=(c*e-b*f)/(a*e-b*d);
   y=(c*d-a*f)/(b*d-a*e);
   return;     
}
void solve1(db a,db b,db c,db d,db e,db f){
    assert(a*e-b*d!=0);
    double x=0.,y=0.;
    x=(c*e-b*f)/(a*e-b*d);
    y=(c*d-a*f)/(b*d-a*e);
    printf("x=%.2lf\ny=%.2lf\n",x,y);
}    
int main(){
    double a=0.,b=0.,c=0.,d=0.,e=0.,f=0.,x=0.,y=0.;
    cin >> a>> b >> c>> d >> e >> f;
    {solve(a,b,c,d,e,f,x,y); //8 arguments
    printf("x=%.2lf\ny=%.2lf\n",x,y);}
    {solve1(a,b,c,d,e,f);}  //6 arguments
    system("pause");
    return 0;
}    
