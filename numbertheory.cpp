ll _gcd(ll a , ll b)
{
	if (a < b) swap(a, b);
    if(b==0) return a;
    a%=b;
    return _gcd(b,a);
}
// BIG p : 1000000000000037 , 100000000003s
ll poww(ll a, ll b, ll md) {
    return (!b ? 1 : (b & 1 ? a * poww(a * a % md, b / 2, md) % md : poww(a * a % md, b / 2, md) % md));
}







