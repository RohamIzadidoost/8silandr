=== SQRT TREE ===

[EXPLANATION]
A data structure that performs range queries on an associative operation in O(1) time with O(N log log N) preprocessing. Unlike Sparse Table, it works for any associative operation (like Addition or Matrix Multiplication), not just idempotent ones. 
It recursively divides the array into sqrt(N) blocks. For a query [L, R]:
1. If L and R are in different blocks: result = Suff[L] op Between(blockL+1, blockR-1) op Pref[R].
2. If L and R are in the same block: recurse into that block.

[USE CASES]
- O(1) Range Sum/Product/GCD queries where updates are rare or non-existent.
- When Sparse Table memory is too high (Sparse Table is O(N log N)).
- Operations that are associative but NOT idempotent (where Sparse Table fails).

[SOLVING STRATEGY]
1. Use a power-of-two size N = 2^k for easier block management.
2. Precompute the "Layer" where two indices i and j first belong to different blocks using bit manipulation: `31 - __builtin_clz(clz_layer[i] ^ clz_layer[j])`.
3. 'pref' and 'suff' arrays store prefix/suffix ops within blocks at each level.
4. 'btwn' stores the result of range ops between full blocks.

[CODE]
const int K = 20;
const int N = 1 << K;
int n, a[N], lg[N], clz[N];
int pref[5][N], suff[5][N], btwn[5][N];

int op(int x, int y) { return x + y; } // Change to min, gcd, etc.

void build(int lay, int l, int r) {
    if (l + 1 >= r) return;
    int b = 1 << ((lg[r - l] + 1) >> 1);
    for (int i = l; i < r; i += b) {
        int rb = min(i + b, r);
        pref[lay][i] = a[i];
        for (int j = i + 1; j < rb; j++) pref[lay][j] = op(pref[lay][j - 1], a[j]);
        suff[lay][rb - 1] = a[rb - 1];
        for (int j = rb - 2; j >= i; j--) suff[lay][j] = op(a[j], suff[lay][j + 1]);
        build(lay + 1, i, rb);
    }
    int cnt = (r - l) / b;
    for (int i = 0; i < cnt; i++) {
        int cur = 0;
        for (int j = i; j < cnt; j++) {
            int val = suff[lay][l + j * b];
            cur = (i == j) ? val : op(cur, val);
            btwn[lay][l + i * cnt + j] = cur;
        }
    }
}

int qry(int l, int r) {
    if (l == r) return a[l];
    if (l + 1 == r) return op(a[l], a[r]);
    int lay = clz[lg[l ^ r]];
    int b = 1 << ((lg[n] + 1) >> 1); // Simplified for top level
    // In practice, use bit tricks or precompute the specific 'b' per layer
    int L = l >> (K - (1 << lay)), R = r >> (K - (1 << lay)); 
    // This is the standard O(1) indexing logic:
    int ly = 0;
    while ( (l >> (lg[n] >> (ly))) == (r >> (lg[n] >> (ly))) ) ly++;
    int sz = lg[n] >> ly;
    int b_sz = 1 << (sz >> 1);
    int b_l = l >> (sz >> 1), b_r = r >> (sz >> 1);
    int res = suff[ly][l];
    if (b_r - b_l > 1) {
        int m = (l >> sz) << sz;
        int cnt = 1 << (sz - (sz >> 1));
        res = op(res, btwn[ly][m + (b_l + 1) * cnt + (b_r - 1)]);
    }
    return op(res, pref[ly][r]);
}

void clr(int m) {
    n = 1; while (n < m) n <<= 1;
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) pref[j][i] = suff[j][i] = btwn[j][i] = 0;
    }
}