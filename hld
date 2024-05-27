void predfs(int v , int p){
	sz[v] = 1 ; if(p != -1) h[v] = h[p] + 1; par[v] = p ; 
	for(auto u : adj[v]){
		if(u != p){
			predfs(u , v) ;
			if(bc[v] == -1 || sz[u] > sz[bc[v]]) bc[v] = u ; 
			sz[v] += sz[u] ; 
		}
	}
}
void dfs(int v , int p , int id){
	t.pb(v) ; 
	st[v] = cnt ; 
	cnt++ ; 
	if(id) hd[v] = v ; 
	else hd[v] = hd[p] ; 
	if(bc[v] != -1){
		dfs(bc[v] , v , 0) ; 
	}
	for(auto u : adj[v]) {
		if(u != p && u != bc[v]) dfs(u , v , 1) ;
	}
}
void getp(int v){
	while(v != -1){
		path.pb({st[hd[v]] , st[v] + 1}) ; 
		v = par[hd[v]] ; 
	}
}
