// UVa11396	Claw Decomposition
// 陈锋
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int MAXV = 300 + 1, BLACK = 2, WHITE = 1;
int V, color[MAXV];
vector<int> G[MAXV];

bool bipartite(int u)
{
	vector<int>& adj = G[u];
	for(int i = 0; i < adj.size(); i++)
	{
		int v = adj[i];
		int& cv = color[v];
		if(cv == color[u]) return false;
		if(cv == 0)
		{
			cv = 3 - color[u];
			if(!bipartite(v)) return false;
		}
	}
	return true;
}

int main() {
	while(true)
	{
		scanf("%d", &V);
		if(V == 0) break;

		int a, b;
		for(int i = 0; i < V; i++)	
			G[i].clear();
		fill(color, color + V + 1, 0);

		while(true)
		{
			scanf("%d %d", &a, &b);
			if(a == 0 || b == 0) break;
			G[a-1].push_back(b-1);
			G[b-1].push_back(a-1);
		}
	
		color[0] = WHITE;
		bool result = bipartite(0);
		puts(result ? "YES" : "NO");
	}

	return 0;
}