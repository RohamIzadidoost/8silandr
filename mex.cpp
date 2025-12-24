=== MEX (MINIMUM EXCLUDED VALUE) ===

[EXPLANATION]
The MEX of a set is the smallest non-negative integer not present in it. 
Key Property: The MEX of a set S is always ≤ |S|. This allows limiting the search range to [0, N] for an array of size N.

[USE CASES]
- Grundy numbers in impartial games (Nim-sum).
- Range MEX queries (finding MEX of a subarray [L, R]).
- Finding the smallest missing ID in a system with updates.

[SOLVING STRATEGY]
1. Static MEX: Use a frequency array or bitset. O(N).
2. Range MEX (Static): 
   - Use a Persistent Segment Tree. 
   - Each leaf 'i' in the tree stores the last index where the value 'i' appeared. 
   - Each internal node stores the minimum 'last seen index' in its range.
   - For a query [L, R], search the version of the tree for prefix R. Find the smallest 'i' such that its last seen index is < L.
3. Range MEX (Dynamic): Use Square Root Decomposition or a Segment Tree of Sets (heavy). Mo's algorithm works in O(N√Q) for offline.

[CODE]
const int N = 2e5 + 5;
const int M = N * 40; // Persistent nodes
int ls[M], rs[M], mn[M], rt[N], nodes;

int upd(int prev, int tl, int tr, int val, int idx) {
    int v = ++nodes;
    ls[v] = ls[prev]; rs[v] = rs[prev];
    if (tl == tr) {
        mn[v] = idx;
        return v;
    }
    int tm = (tl + tr) / 2;
    if (val <= tm) ls[v] = upd(ls[prev], tl, tm, val, idx);
    else rs[v] = upd(rs[prev], tm + 1, tr, val, idx);
    mn[v] = min(mn[ls[v]], mn[rs[v]]);
    return v;
}

int qry(int v, int tl, int tr, int L) {
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    if (mn[ls[v]] < L) return qry(ls[v], tl, tm, L);
    return qry(rs[v], tm + 1, tr, L);
}

void clr(int n) {
    for (int i = 0; i <= nodes; i++) ls[i] = rs[i] = mn[i] = 0;
    for (int i = 0; i <= n; i++) rt[i] = 0;
    nodes = 0;
}

/* Usage for Range MEX:
for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    if (x > n) x = n + 1; // Values > n don't affect MEX
    rt[i] = upd(rt[i-1], 0, n + 1, x, i);
}
int res = qry(rt[R], 0, n + 1, L);
*/