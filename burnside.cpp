=== BURNSIDE'S LEMMA & POLYA ENUMERATION ===

[EXPLANATION]
Burnside's Lemma counts distinct objects under a symmetry group G. The number of orbits (distinct colorings) is the average number of fixed points: 
|Orbits| = (1/|G|) * sum_{g in G} (fixed_points(g)).
Pólya Enumeration Theorem (PET) states that for colorings with 'm' colors, fixed_points(g) = m^c(g), where c(g) is the number of disjoint cycles in the permutation g.

[USE CASES]
- Counting distinct necklaces/bracelets (rotations/reflections).
- Counting distinct colorings of a cube, grid, or graph under symmetry.
- Any "number of ways to color X such that rotations/flips are the same" problem.

[SOLVING STRATEGY]
1. Identify the size of the symmetry group |G|.
2. For each symmetry g, determine the number of cycles c(g) it induces on the elements.
3. For rotation by k in a set of N elements: c(g) = gcd(k, N).
4. For reflections in a regular N-gon:
   - N is odd: N axes through a vertex and midpoint of opposite edge, each has (N+1)/2 cycles.
   - N is even: N/2 axes through opposite vertices (N/2 + 1 cycles) and N/2 axes through midpoints (N/2 cycles).
5. Result = (sum(m^c(g)) * inv(|G|)) % MOD.

[CODE]
typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
int p[N], vis[N];

ll pwr(ll a, ll b) {
    ll r = 1; a %= MOD;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return r;
}

ll inv(ll n) { return pwr(n, MOD - 2); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll neck(ll n, ll m) {
    ll s = 0;
    for (int i = 0; i < n; i++) s = (s + pwr(m, gcd(i, n))) % MOD;
    return s * inv(n) % MOD;
}

ll brac(ll n, ll m) {
    ll s = neck(n, m) * n % MOD;
    if (n & 1) s = (s + n * pwr(m, (n + 1) / 2)) % MOD;
    else s = (s + (n / 2) * pwr(m, n / 2 + 1) + (n / 2) * pwr(m, n / 2)) % MOD;
    return s * inv(2 * n) % MOD;
}

int get_c(int n) {
    int c = 0;
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            c++;
            for (int j = i; !vis[j]; j = p[j]) vis[j] = 1;
        }
    }
    return c;
}

void clr(int n) {
    for (int i = 0; i <= n; i++) p[i] = vis[i] = 0;
}