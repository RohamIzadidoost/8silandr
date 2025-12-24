=== COUNTING LABELED GRAPHS (COMPLETE) ===

[EXPLANATION]
1. Total: G(n) = 2^(n*(n-1)/2).
2. Connected: C(n) = G(n) - (1/n) * sum_{k=1 to n-1} [k * comb(n, k) * C(k) * G(n-k)].
   Alternative: C(n) = G(n) - sum_{k=1 to n-1} [comb(n-1, k-1) * C(k) * G(n-k)].
3. Exactly k components: DP state dp[i][j] is the number of graphs with i vertices and j components.
   dp[i][j] = sum_{s=1 to i-j+1} [comb(i-1, s-1) * C(s) * dp[i-s][j-1]].
4. With m edges: Total is comb(n*(n-1)/2, m).
5. Connected with m edges: C(n, m) = comb(N, m) - sum_{k=1 to n-1} [comb(n-1, k-1) * sum_{p=0 to m} (C(k, p) * comb((n-k)*(n-k-1)/2, m-p))].
   where N = n*(n-1)/2.

[USE CASES]
- Problems asking for "Exactly K connected components".
- Finding the number of connected graphs with a fixed number of edges (n-1 for trees, n for unicyclic).
- Generating functions: C(x) = ln(G(x)) where G(x) is the EGF of all labeled graphs.

[SOLVING STRATEGY]
1. If only N is given (N <= 5000), use the O(N^2) C(n) recurrence.
2. If N and K (components) are given, use the O(N^2 * K) DP.
3. If N and M (edges) are given, use the O(N^3 * M) or O(N^2 * M) DP depending on constraints.
4. For very large N, use NTT to compute the polynomial logarithm of the EGF.

[CODE]
typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 505;
ll g[N], c[N], dp[N][N], b[N][N];

ll pwr(ll a, ll b) {
    ll r = 1; a %= MOD;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return r;
}

void prec(int n) {
    for (int i = 0; i <= n; i++) {
        b[i][0] = 1;
        for (int j = 1; j <= i; j++)
            b[i][j] = (b[i-1][j-1] + b[i-1][j]) % MOD;
    }
    for (int i = 1; i <= n; i++) g[i] = pwr(2, (ll)i * (i - 1) / 2);
    for (int i = 1; i <= n; i++) {
        c[i] = g[i];
        ll sub = 0;
        for (int k = 1; k < i; k++) {
            ll res = (b[i-1][k-1] * c[k]) % MOD;
            res = (res * g[i-k]) % MOD;
            sub = (sub + res) % MOD;
        }
        c[i] = (c[i] - sub + MOD) % MOD;
    }
}

void comp(int n, int k_max) {
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k_max; j++) {
            for (int s = 1; s <= i - j + 1; s++) {
                ll res = (b[i-1][s-1] * c[s]) % MOD;
                res = (res * dp[i-s][j-1]) % MOD;
                dp[i][j] = (dp[i][j] + res) % MOD;
            }
        }
    }
}

void clr(int n) {
    for (int i = 0; i <= n; i++) {
        g[i] = c[i] = 0;
        for (int j = 0; j <= n; j++) {
            b[i][j] = dp[i][j] = 0;
        }
    }
}

================================================================================
                    PRUFER SEQUENCES & TREE ENUMERATION
================================================================================

[1. PRUFER SEQUENCE BASICS]
- A Prüfer sequence uniquely represents a labeled tree of N nodes using a 
  sequence of length N-2.
- Bijection: {Labeled Trees with N nodes} <-> {Sequences of length N-2 in [1, N]}.
- Cayley's Formula: Total number of labeled trees = N^(N-2).

[2. CONSTRUCTION & RECONSTRUCTION]
- Tree to Sequence (O(N)): Repeatedly remove the leaf with the smallest label 
  and append its neighbor's label to the sequence.
- Sequence to Tree (O(N)): Maintain degrees of all nodes (deg = freq_in_seq + 1). 
  Connect the first element of the sequence to the smallest label with deg=1.

[3. THE DEGREE PROPERTY (MOST IMPORTANT)]
- Node 'i' appears in the Prüfer sequence exactly (deg(i) - 1) times.
- Application: Count trees with fixed degrees d1, d2, ..., dN:
  Formula: (N-2)! / [ (d1-1)! * (d2-1)! * ... * (dN-1)! ]
  (This is the Multinomial Coefficient).

[4. MATRIX TREE THEOREM (GENERAL GRAPHS)]
To count the number of spanning trees in a general graph G:
1. Construct the Laplacian Matrix L = D - A.
   - D: Diagonal matrix where D[i][i] = degree of node i.
   - A: Adjacency matrix where A[i][j] = number of edges between i and j.
2. Delete any row 'r' and any column 'c' (usually r=c) to get matrix L'.
3. Number of spanning trees = |det(L')|.
4. Complexity: O(N^3) via Gaussian Elimination.

[5. DIRECTED SPANNING TREES (ARBORESCENCES)]
To count spanning trees rooted at 'R' in a directed graph:
1. L = D_in - A. (D_in is the in-degree matrix).
2. Spanning trees rooted at R (edges point toward R) = det of L with row/col R removed.
3. If edges point AWAY from R, use D_out instead.

[6. BEST'S THEOREM (EULERIAN CIRCUITS)]
Number of Eulerian circuits in a directed graph G:
- Formula: ec(G) = t_w(G) * Product_{v in V} (deg_out(v) - 1)!
- t_w(G) is the number of arborescences rooted at any node w.

[7. MATRIX TREE THEOREM WITH WEIGHTS]
- To find the sum of products of edge weights for all spanning trees:
  Set A[i][j] = sum of weights of edges between i and j.
  Set D[i][i] = sum of weights of all edges incident to i.
  Result = det(L' with row/col removed).

[8. LGV LEMMA (NON-INTERSECTING PATHS)]
Counting non-intersecting paths from A={a1..ak} to B={b1..bk} in a DAG:
1. Create matrix M where M[i][j] = number of paths from ai to bj.
2. Result = det(M).

================================================================================