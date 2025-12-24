mt19937 Rnd;
int Rand(int l, int r)
{
    return (Rnd() % (r - l + 1) + l);
}
Rnd.seed(time(0));

=== ZOBRIST & STRING HASHING ===

[USE CASE]
- Checking if two subtrees are isomorphic.
- Finding if a range [L, R] contains a permutation of [1, K].
- Substring equality in O(1).

[CODE - ZOBRIST FOR PERMUTATIONS]
uint64_t val[N], pref[N];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void init(int n) {
    for(int i=1; i<=n; i++) val[i] = rng();
}
// Range [l, r] is a permutation of [1, r-l+1] if:
// (pref[r] ^ pref[l-1]) == (val[1] ^ val[2] ^ ... ^ val[r-l+1])