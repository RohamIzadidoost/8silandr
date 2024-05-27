const int FN = 2 * maxn , FM = maxn * maxn / 2 ; 
int head[FN], Q[FN*30], par[FN], inq[FN], L, R;
ld dist[FN], cost[FM<<1], ans;
const ld eps=1e-7;
inline void add_edge(int u, int v, int c, ld w){
	to[M]=v, cap[M]=c, cost[M]=w, prv[M]=head[u], head[u]=M++;
	to[M]=u, cap[M]=0, cost[M]=-w, prv[M]=head[v], head[v]=M++;
}
bool Flow(int src, int snk){
	fill(dist, dist+FN, inf);
	L=R=0;
	dist[Q[R++]=src]=0;
	inq[src]=1;
	bool res=0;
	while (L^R){
		int v=Q[L++];
		res|=(v==snk);
		inq[v]=0;
		for (int i=head[v]; ~i; i=prv[i]) if (cap[i]){
			int u=to[i];
			if (dist[u]>1e-7+dist[v]+cost[i]){
				dist[u]=dist[v]+cost[i];
				par[u]=i;
				if (!inq[u]){
					inq[u]=1;
					Q[R++]=u;
				}
			}
		}
	}
	if (!res) return 0;
	ans+=dist[snk];
	int v=snk;
	while (v^src){
		int i=par[v];
		cap[i]--;
		cap[i^1]++;
		v=to[i^1];
	}
	return 1;
}
//	memset(head, -1, sizeof(head));
