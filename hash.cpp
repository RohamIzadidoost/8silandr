ll hsh(int l , int r){
	return (h[r] - h[l] * pt[r-l] % mod + mod) % mod ; 
}
