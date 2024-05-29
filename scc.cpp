void sfd(int v , int c)
{
	comp[v] = c ; 
	for(auto u : radj[v])
	{
		if(comp[u] == 0)
		{
			sfd(u , c) ; 
		}
	}
}

void dfs(int v)
{
	mark[v] = 1 ; 
	for(auto u : adj[v])
	{
		if(mark[u.X] == 0 )
		{
			dfs(u.X) ; 
		}
	}
	t.pb(v) ; 
}

reverse(t.begin() , t.end()) ; 
for(auto v : t)
	{
		if(comp[v] == 0 ) sfd(v , cnt++) ; 
	}
