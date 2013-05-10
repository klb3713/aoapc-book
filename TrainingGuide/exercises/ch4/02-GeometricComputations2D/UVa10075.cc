// UVa10075 Airlines
// 陈锋
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const double PI = 3.141592653589793, R = 6378;
struct City{
    double latitude, longitude;
};
istream& operator>>(istream& is, City& c){ return is>>c.latitude>>c.longitude; }

inline double conv(double deg) { return deg * PI / 180; }

const int MAXN = 100 + 10;
int N, M, Q;
City cities[MAXN];
map<string, int> names;
double d[MAXN][MAXN];

double dist(const City& c1, const City& c2){
    double lng1 = conv(c1.longitude), lat1 = conv(c1.latitude),
        lng2 = conv(c2.longitude), lat2 = conv(c2.latitude);
    double c = acos(cos(lat1)*cos(lat2)*cos(lng1 - lng2) + sin(lat1)*sin(lat2));
    return floor(R * c + .5);
}

void solve(){
    string a, b;
    
    for(int i = 0; i < N; i++) {
        cin>>a>>cities[i];
        names[a] = i;
        
        for(int j = 0; j < N; j++)
            d[i][j] = DBL_MAX;
        d[i][i] = 0;
    }

    for(int i = 0; i < M; i++)
    {
        cin>>a>>b;
        int i1 = names[a], i2 = names[b];
        d[i1][i2] = dist(cities[i1], cities[i2]);
    }
    
    // Floyd求最短路
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if(d[i][k] < DBL_MAX && d[k][j] < DBL_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    for(int i = 0; i < Q; i++) {
        cin>>a>>b;
        int i1 = names[a], i2 = names[b];
        double ans = d[i1][i2];
        if(ans < DBL_MAX) cout<<ans<<" km"<<endl;
        else cout<<"no route exists"<<endl;
    }
}

int main() {
    int c = 1;
    while(true) {
        cin>>N>>M>>Q;
        if(!N) break;
        if(c > 1) cout<<endl;
        cout<<"Case #"<<c<<endl;
        c++;
        solve();
    }
    
    return 0;
}
