#include<iostream>
#include<iomanip>
using namespace std;
double a=0,b=0,c=0,d=0,e=0,f=0,x=0,y=0;
int solve(){
    if(a*e-b*d==0){
        if(c*d-a*f==0) return 0;
        else return -1;
    }
    else {
        x=(c*e-b*f)/(a*e-b*d);
        y=(c*d-a*f)/(b*d-a*e); 
        return 1;
    }     
}    
int main()
{
    int flag;
    cin >> a>>b>>c>>d>>e>>f;
    flag=solve();
    if(flag==1)
        cout << setiosflags(ios::fixed)
             << setprecision(2)
             <<"x=" << x <<"\ny="<< y<<endl;
    else if(flag==-1) cout <<"No answer"<< endl;
    else cout <<"Unlimited answers" << endl;         
    system("pause");
    return 0;
}    
