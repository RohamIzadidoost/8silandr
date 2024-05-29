struct MAT {
	long long  n , m , A[200][200] ; 
	MAT (const long long  &n2 ,const long long  &m2 ){
		n = n2 , m = m2 ; 
		for (int i = 0 ; i < n ; i++)
			for (int j = 0 ; j < m ; j++)
				A[i][j] = 0 ; 
	}
	MAT operator * (const MAT &B){
		MAT C = MAT(n , m) ; 
		for (int i = 0 ; i < n ; i++){
			for (int j = 0 ; j < m ; j++){
				for (int k = 0 ; k < m ; k++)
					C.A[i][j] = (C.A[i][j] + 1ll * A[i][k] * B.A[k][j] % (mod-1)) % (mod - 1) ; 
			}
		}
		return (C) ; 
	}
	void eq(const ll (&a)[5][5] , int n , int m )
	{
		for(int i = 0 ; i < n ; i ++ )
		{
			for(int j = 0 ; j < m ; j ++ )
			{
				A[i][j] = a[i][j] ; 
			}
		}
	}
	
	MAT operator + (const MAT &B){
		MAT C = MAT(n , m) ; 
		for (int i = 0 ; i < n ; i++){
			for (int j = 0 ; j < m ; j++)
				C.A[i][j] = (A[i][j] + B.A[i][j]) % mod  ; 
		}
		return (C) ; 
	}
	void  printt (){
		for (int i = 0 ; i < n ; i++){
			for (int j = 0 ; j < m ; j++ )
				cout<<A[i][j]<<" "; 
			cout<<"\n" ;
		}
	}
	MAT operator ^ (long long  x){
		MAT R = MAT(n , m) ; 
		for (int i = 0 ; i < n ; i++)
			R.A[i][i] = 1 ;
		MAT T = MAT(n , m) ; 
		for (int i = 0 ; i < n ;i++)
			for (int j = 0 ;j < m ;j++)
				T.A[i][j] = A[i][j] ; 
		while (x > 0){
			if (x%2)
				R = R * T ; 
			T = T * T ; 
			x/=2 ; 
		}
		return R ;
	}
};
