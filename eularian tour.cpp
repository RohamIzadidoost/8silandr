void tour(int v , int b)
{
	if(b == 0) M[v] = 1 ; 
	while( adj[v][b] .size())
	{
		auto k = adj[v][b].back() ; int u = k.X , id = k.Y ;  
		adj[v][b].pop_back() ; 
		if(mark[id] == 0)
		{
			mark[id]  = 1 ; 
			tour(u , 1 -  b) ; 
		}
	}
	ans.pb(v) ;  
	a.pb({v , b}) ; 
}
 
