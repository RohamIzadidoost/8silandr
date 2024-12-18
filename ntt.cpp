 
inline void fix(ll &x){
	if (x<0) x+=mod;
	if (x>=mod) x-=mod;
}
ll powmod(ll a, ll b){
	ll res=1;
	for (; b; b>>=1, a=a*a%mod) if (b&1) res=res*a%mod;
	return res;
}
ll nCr(int n, int r){
	if (r<0 || r>n) return 0;
	return F[n]*I[r]%mod*I[n-r]%mod;
}
 
void NTT(ll* F, int n, bool inv){
	int lg=ceil(log2(n));
	n=1<<lg;
	//debug2(n, lg)
	for (int i=0; i<n; i++) rev[i]=(rev[i>>1]>>1) | ((i&1)<<(lg-1));
	for (int i=0; i<n; i++) if (i<rev[i]) swap(F[i], F[rev[i]]);
	for (int len=1; len<n; len<<=1){
		ll wn=powmod(3, (mod-1)/(2*len));
		if (inv) wn=powmod(wn, mod-2);
		for (int i=0; i<n; i+=2*len){
			ll w=1;
			for (int j=i; j<i+len; j++){
				ll x=(F[j] + F[j+len]*w)%mod;
				ll y=(F[j] - F[j+len]*w)%mod;
				F[j]=x;
				F[j+len]=y;
				w=w*wn%mod;
			}
		}
	}
	if (inv){
		ll invn=powmod(n, mod-2);
		for (int i=0; i<n; i++) F[i]=F[i]*invn%mod;
	}
}
 