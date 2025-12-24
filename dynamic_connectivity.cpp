=== DYNAMIC DATA STRUCTURES: DELETION VIA TIMELINE TREE ===

[EXPLANATION]
This technique (Divide and Conquer over Queries) allows any data structure that supports "Add" and "Rollback" to effectively support "Delete". 
1. The "lifetime" of an element is the interval [L, R] of query indices during which it exists.
2. Build a Segment Tree where the leaves are the query timestamps [1, Q].
3. Store each element in the O(log Q) nodes of the tree that cover its lifetime.
4. Perform a DFS on the tree:
   - Entering a node: Apply all "Add" operations stored there to your data structure.
   - At a leaf: The data structure now reflects the state at that timestamp; answer the query.
   - Exiting a node: Rollback the operations performed when you entered.

[USE CASES]
- Offline Dynamic Connectivity: Count components or check connectivity with edge additions/deletions.
- Dynamic Linear Basis: Find max XOR in a set of numbers where numbers are added and removed.
- Dynamic Convex Hull: Maintain a set of lines and query max/min at a point.

[SOLVING STRATEGY]
- Data Structure Choice: Must support Rollback (usually via a stack). DSU must use Union-by-Rank/Size (NOT path compression) to keep find() at O(log N).
- Edge Lifetimes: Use a `map<pair<int, int>, int>` to track when an element was added to determine its [L, R] interval when it is deleted.
- Memory: Segment Tree nodes store vectors of elements. Total memory is O(N log Q).

[CODE - DYNAMIC CONNECTIVITY EXAMPLE]
const int N = 2e5 + 5;
struct edge { int u, v; };
vector<edge> t[4 * N];
int p[N], sz[N], ans[N], comps, n, q;
struct log { int u, v, s; };
vector<log> stk;

int find(int i) {
    while (i == p[i]) i = p[i];
    return i;
}

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    stk.push_back({u, v, sz[u] == sz[v]});
    p[v] = u;
    if (sz[u] == sz[v]) sz[u]++;
    comps--;
}

void rollback(int lim) {
    while (stk.size() > lim) {
        log l = stk.back(); stk.pop_back();
        p[l.v] = l.v;
        if (l.s) sz[l.u]--;
        comps++;
    }
}

void add(int v, int tl, int tr, int l, int r, edge e) {
    if (l > r) return;
    if (l == tl && r == tr) t[v].push_back(e);
    else {
        int tm = (tl + tr) / 2;
        add(2*v, tl, tm, l, min(r, tm), e);
        add(2*v+1, tm+1, tr, max(l, tm+1), r, e);
    }
}

void dfs(int v, int tl, int tr) {
    int cur = stk.size();
    for (edge& e : t[v]) unite(e.u, e.v);
    if (tl == tr) ans[tl] = comps;
    else {
        int tm = (tl + tr) / 2;
        dfs(2*v, tl, tm); dfs(2*v+1, tm+1, tr);
    }
    rollback(cur);
}

void solve() {
    map<pair<int, int>, int> act;
    comps = n;
    for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    // ... Read queries, if add: act[{u,v}]=i, if del: add(1,1,q,act[{u,v}],i-1,{u,v}) ...
    // ... After loop, for any remaining in map: add(1,1,q,start,q,{u,v}) ...
    dfs(1, 1, q);
}