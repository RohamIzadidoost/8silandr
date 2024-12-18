#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll ;
#define pll pair<ll , ll >
#define X   first
#define Y   second
#define mp  make_pair
#define pii pair<int , int>
#define file_io freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#define migmig ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pb push_back
// BIG p : 1000000000000037 , 100000000003
ll poww(ll a, ll b, ll md) {
    return (!b ? 1 : (b & 1 ? a * poww(a * a % md, b / 2, md) % md : poww(a * a % md, b / 2, md) % md));
}
const int maxn = 1000*100+5 ;
const ll inf = 9223372036854775807 ;
const ll mod = 1e9 + 7 ;
const int lg = 20 ;

int main()
{
	migmig ;

}









