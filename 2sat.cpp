//harki mesle i khodesh 2 * i notesh 2 * i + 1 he
//yale u -> v yani agar u yek baseh v ham bayad yek bashe
vector<int> out[maxn * 2] , in[maxn * 2] , topol , adj[maxn];
 
bool visited[maxn * 2];
 
int color[maxn * 2] , c , val[maxn] , r[maxn] ;
 
void add_edge(int v , int u)
{
	out[v].pb(u);
	in[u].pb(v);
}
 
void dfs(int v)
{
	visited[v] = 1;
	for(auto u : out[v])
		if(!visited[u])
			dfs(u);
	topol.pb(v);
}
 
void sfd(int v)
{
	visited[v] = 1;
	color[v] = c;
	for(auto u : in[v])
		if(!visited[u])
			sfd(u);
}
for(int i = 0; i < 2 * n; i++)
		if(!visited[i])
			dfs(i);
reverse(topol.begin() , topol.end());
memset(visited , 0 , sizeof visited);
for(int v = 1 ; v <= 2 * m + 1 ; v ++ )
		if(!visited[v])
			sfd(v) , c++;
	for(int i = 1; i <= m; i++)
		if(color[2 * i] == color[2 * i + 1])
			return cout << "NO" << endl , 0;
