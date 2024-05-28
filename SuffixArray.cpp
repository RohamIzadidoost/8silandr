ll n , p[maxn] , h[lg][maxn] , sa[maxn] , lcp[maxn] , mark[maxn] , ps[maxn] , l[maxn] , r[maxn] , cp , ans ; 
string s , t ; 
stack<int> st ; 
bool cmp(int i , int j){
	if(h[cp-1][i] < h[cp-1][j]) return true; 
	if(h[cp-1][i] > h[cp-1][j]) return false ; 
	if(i + (1 << (cp-1)) > n + 1 || j + (1 << (cp-1)) > n + 1) return i < j ;  
	return h[cp-1][i + (1 << (cp-1))] < h[cp-1][j + (1 << (cp-1))] ; 
}
void SA(){
	for(int i = 1 ; i <= n ; i ++ ) p[i] = i , h[0][i] = s[i]; 
	for(cp = 1 ; cp < lg ; cp++ ){
		sort(p +1 , p + n + 1 , cmp) ; 
		h[cp][p[1]] =1 ; 
		for(int i = 2 ; i <= n ; i ++ ) h[cp][p[i]] = h[cp][p[i-1]] + cmp(p[i-1] , p[i]) ; 
	}
}
void Lcp(){
	for(int i = 1 , k = 0 ; i <= n ; i ++ ){
		if(sa[i] == n) continue ; 
		for(int j = p[sa[i] + 1] ; k <= n && s[i+k] == s[j+k] ; ) k++ ; 
		lcp[sa[i]] = k ; 
		if(k) k -- ; 
	}
}
