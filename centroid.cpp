void plant(int v , int p = -1)
{
  	sz[v] = 1;
  	for(auto u : adj[v])
      	if(u != p && !hide[u])
        {
          	plant(u , v);
          	sz[v] += sz[u];
        }
}//
int find_centroid(int v , int n , int p = -1)
{
    bool found = 1;
  	while(found)
    {
      	found = 0;
       	for(auto u : adj[v])
      		if(u != p && !hide[u] && sz[u] * 2 > n)
            {
              	found = 1;
              	p = v;
              	v = u;
              	break;
            }
    }
  	return v;
}
void solve(int v , int h = 0)
{
	plant(v);
	v = find_centroid(v , sz[v]);
  	cout<<v <<"  level " << h << endl ; 
  	hide[v] = 1;	
  	for(auto u : adj[cent])
      	if(!hide[u])
          	solve(u , h + 1);
}
