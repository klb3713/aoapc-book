// UVa11589 Save the President
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

#define REP(i,n)           for(int i = 0; i < (n); ++i)
#define FOR(i,s,t)         for(int i = (s); i <= (t); ++i)
#define exp(i,b0,b1,b2,b3) { b0 = i&1; b1 = (i>>1)&1; b2 = (i>>2)&1; b3 = (i>>3); }
#define coeff(b0,b1,b2,b3) ((b0 + b1 + b2 + b3) % 2 == 1 ? 1 : -1)

int ord(string s) {
	int h, m;
	sscanf(s.c_str(), "%d:%d", &h, &m);
	return h * 4 + m / 15;
}

int S[20][20][20][100];
int main() {
	int N, T = 0;
	while(cin >> N, N) {
		int dx, dy, dz, Q;
		int b0, b1, b2, b3;
		cout << "3D World " << ++T << ":\n";
		cin >> dx >> dy >> dz >> Q;
		memset(S, 0, sizeof(S));
		while(N--) {
			int x1, y1, z1, x2, y2, z2;
			string s1, s2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> s1 >> s2;
			int t1 = ord(s1), t2 = ord(s2);
			x1++; y1++; z1++; t1++;
			FOR(x,x1,x2) FOR(y,y1,y2) FOR(z,z1,z2) FOR(t,t1,t2) S[x][y][z][t] = 1;
		}
		int cnt=0;
		FOR(x,1,dx) FOR(y,1,dy) FOR(z,1,dz) FOR(t,1,96) FOR(i,1,15) {
			exp(i,b0,b1,b2,b3);
			S[x][y][z][t] += S[x-b0][y-b1][z-b2][t-b3] * coeff(b0,b1,b2,b3);
		}
		while(Q--) {
			int xq, yq, zq;
			string sq;
			cin >> xq >> yq >> zq >> sq;
			int tq = ord(sq);
			int ans = 0;
			FOR(x,1,dx-xq+1) FOR(y,1,dy-yq+1) FOR(z,1,dz-zq+1) FOR(t,1,96-tq+1) {
				int s = 0;
				REP(i,16) {
					exp(i,b0,b1,b2,b3);
					s -= S[x-1+b0*xq][y-1+b1*yq][z-1+b2*zq][t-1+b3*tq] * coeff(b0,b1,b2,b3);
				}
				if(!s) ans++;
			}
			if(ans) cout << ans << " safe place(s) found\n";
			else cout << "No safe place(s) found\n";
		}
	}
	return 0;
}
