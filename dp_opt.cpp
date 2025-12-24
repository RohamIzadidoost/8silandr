=== DP OPTIMIZATIONS CHEATSHEET ===

[1. CONVEX HULL TRICK (CHT) - MONOTONIC]
- Form: dp[i] = min(dp[j] + m[j]*x[i] + c[j]) where m[j] is monotonic.
- Strategy: Maintain a lower hull of lines. If slopes and x-queries are both monotonic, use a Deque (O(N)).
- Code:
struct L { ll m, c; ll f(ll x) { return m*x + c; } };
L q[N]; int h, t;
bool bad(L a, L b, L c) { return (__int128)(b.c-a.c)*(b.m-c.m) >= (__int128)(c.c-b.c)*(b.m-a.m); }
void add(ll m, ll c) {
    L l = {m, c};
    while(t-h >= 2 && bad(q[t-2], q[t-1], l)) t--;
    q[t++] = l;
}
ll qry(ll x) {
    while(t-h >= 2 && q[h].f(x) >= q[h+1].f(x)) h++;
    return q[h].f(x);
}

[2. LI CHAO TREE - NON-MONOTONIC CHT]
- Form: Same as CHT, but slopes or x-queries are arbitrary.
- Strategy: Segment tree where each node stores the "dominant" line for its range. O(log Range).
- Code:
struct L { ll m, c; ll f(ll x) { return m*x + c; } } tr[4*N];
void ins(int v, int l, int r, L nl) {
    int m = (l+r)/2;
    bool bl = nl.f(l) < tr[v].f(l), bm = nl.f(m) < tr[v].f(m);
    if(bm) swap(tr[v], nl);
    if(l == r) return;
    if(bl != bm) ins(2*v, l, m, nl);
    else ins(2*v+1, m+1, r, nl);
}
ll qry(int v, int l, int r, int x) {
    ll res = tr[v].f(x);
    if(l == r) return res;
    int m = (l+r)/2;
    if(x <= m) return min(res, qry(2*v, l, m, x));
    return min(res, qry(2*v+1, m+1, r, x));
}

[3. DIVIDE AND CONQUER (D&C)]
- Form: dp[k][i] = min_{j<i} (dp[k-1][j] + cost(j, i))
- Condition: Quadrangle Inequality on cost: cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c) for a<b<c<d.
- Opt: opt[k][i] <= opt[k][i+1]. O(K N log N).
- Code:
void compute(int k, int L, int R, int oL, int oR) {
    if(L > R) return;
    int m = (L+R)/2, p = -1; dp[k][m] = INF;
    for(int i=oL; i<=min(m, oR); i++) {
        ll cur = dp[k-1][i] + cost(i, m);
        if(cur < dp[k][m]) { dp[k][m] = cur; p = i; }
    }
    compute(k, L, m-1, oL, p); compute(k, m+1, R, p, oR);
}

[4. KNUTH OPTIMIZATION]
- Form: dp[i][j] = min_{i<k<j} (dp[i][k] + dp[k][j]) + cost(i, j)
- Condition: opt[i][j-1] <= opt[i][j] <= opt[i+1][j].
- Opt: Reduces O(N^3) to O(N^2).
- Code:
for(int i=n; i>=1; i--) {
    for(int j=i+1; j<=n; j++) {
        if(j-i == 1) { dp[i][j] = 0; opt[i][j] = i; continue; }
        dp[i][j] = INF;
        for(int k=opt[i][j-1]; k<=opt[i+1][j]; k++) {
            ll v = dp[i][k] + dp[k][j] + cost(i, j);
            if(v < dp[i][j]) { dp[i][j] = v; opt[i][j] = k; }
        }
    }
}

[5. ALIENS TRICK (WQS BINARY SEARCH)]
- Form: dp[k][n] is the max value using exactly k items. f(k) must be concave/convex.
- Strategy: Binary search a penalty 'p' for using an item. Solve f(p) = max(dp[n] - p*count).
- Code:
while(lo <= hi) {
    mid = (lo+hi)/2;
    auto res = check(mid); // returns {max_val, count}
    if(res.cnt >= K) { ans = res.val + K*mid; lo = mid+1; }
    else hi = mid-1;
}

[6. SLOPE TRICK]
- Form: dp[i][j] = min_{k<=j} (dp[i-1][k] + |j - a[i]|). dp functions are convex.
- Strategy: Maintain the "slopes" of the convex function using two priority queues (left and right).
- Use Case: Problems like "make array non-decreasing with min cost sum|a[i] - b[i]|".
- Code:
priority_queue<int> pq; ll ans = 0;
for(int x : a) {
    pq.push(x); pq.push(x);
    ans += pq.top() - x;
    pq.pop();
} // Result is ans