inline void add(int ind , ll i , ll v){
	for(i ++ ; i < mod ; i += i & -i){
		fen[ind][i] += v ; 
		//cout <<" bomb " << i << endl ; 
	}
}
inline void ADD(ll l , ll r , ll x){
	add(0 , l , x) ; 
	add(0 , r+1 , -1 * x) ; 
	add(1 , l , x * (l - 1ll)) ; 
	add(1 , r + 1 , -1 * x * r) ; 
}
ll get(int ind , ll i){
	ll res =0 ; 
	for(i ++ ; i > 0 ; i -= i & -i){
		if(fen[ind].find(i) != fen[ind].end())
			res += fen[ind][i] ; 
	}
	return res ; 
}
ll GET(ll i){
	return get(0 , i) * i - get(1 , i) ; 
}
