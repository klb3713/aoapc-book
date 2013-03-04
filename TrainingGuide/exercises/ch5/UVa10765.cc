// UVa10765 Doves and Bombs
// 陈锋
#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
#include<set>
#include<algorithm>
using namespace std;

struct Edge
{
	int u, v;
};

struct value_data
{
	int u, value;
	bool operator<(const struct value_data& rhs) const
	{
		return (value > rhs.value) || ( value == rhs.value && u < rhs.u);
	}
};

const int MAXN = 30000 + 5;
int N, M, pre[MAXN], bccno[MAXN], dfs_clock, bcc_cnt;
bool iscut[MAXN];
vector<int> G[MAXN], bcc[MAXN];

stack<Edge> S;

int dfs(int u, int fa)
{
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		Edge e = {u, v};
		if(!pre[v]) // v还没访问过
		{
			S.push(e);
			child++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if(lowv >= pre[u])
			{
				iscut[u] = true;
				vector<int>& cur_bcc = bcc[++bcc_cnt];
				cur_bcc.clear();
				while(true)
				{
					Edge x= S.top(); S.pop();
					if(bccno[x.u] != bcc_cnt)
					{
						cur_bcc.push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if(bccno[x.v] != bcc_cnt)
					{
						cur_bcc.push_back(x.v);
						bccno[x.v] = bcc_cnt;
					}
					if(x.u == u && x.v == v) break;
				}
			}
		}
		else if(pre[v] < pre[u] && v != fa)
		{
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}
	
	if(fa < 0 && child == 1) iscut[u] = false;
	return lowu;
}

void find_bcc(int n)
{
	// 调用结束后S保证为空
	fill_n(pre, n, 0);
	fill_n(iscut, n, false);
	fill_n(bccno, n, 0);
	dfs_clock = bcc_cnt = 0;
	for(int i = 0; i < n; i++)
		if(pre[i] == 0) dfs(i, -1);
}

/*
	得到结点u的鸽子值，如果u是割顶，那么就是它周围相连的bcc个数
	否则属于一个bcc，就算删除，整个图依然连通的，所以鸽子值是1
*/
int value(int u)
{
	if(iscut[u])
	{
		set<int> bccs;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			bccs.insert(bccno[v]);
		}
		return bccs.size();
	}	
	else
	{
		return 1;
	}
}

int main() {
	set<value_data> result;
	while(true)
	{
		scanf("%d %d", &N, &M);
		if(N == 0) break;

		for(int i = 0; i < N; i++)
			G[i].clear();

		int x, y;
		while(true){
			scanf("%d %d", &x, &y);
			G[x].push_back(y);
			G[y].push_back(x);
			if(x == -1) break;
		}
		
		//先求出所有割顶, 同时求出各个点所在的双连通分量编号
		find_bcc(N);		
		result.clear();
		for(int i = 0; i < N; i++)
		{
			value_data data = {i, value(i)};
			result.insert(data);
		}
		
		set<value_data>::iterator cur = result.begin();
		for(int i = 0; i < M; i++)
		{
			printf("%d %d\n", cur->u, cur->value);
			cur++;
		}
		puts("");
	}

	return 0;
}