//Aho 
void AddTrie(){
    int v=0;
    for (char ch:S){
        if (!C[v][ch-'a']) C[v][ch-'a']=++ts;
        v=C[v][ch-'a'];
    }
    ted[v]++;
}
void BuildAho(){
    for (int i=0; i<SGM; i++) if (C[0][i]) Q[R++]=C[0][i];
    while (L<R){
        int v=Q[L++];
        ted[v]++;
        for (int i=0; i<SGM; i++){
            if (!C[v][i]) C[v][i]=C[F[v]][i];
            else{
                F[C[v][i]]=C[F[v]][i];
                Q[R++]=C[v][i];
            }
        }
    }
}//
for(int i = 1 ; i <= ts  ; i++ ) adj[f[i]].pb(i) ;
=== AHO-CORASICK APPLICATIONS ===

[APPLICATION 1: PATTERN COUNTING (TEXT SEARCH)]
To count how many times each pattern appears in a text T:
1. Traverse the DFA with T, marking each node 'v' visited: `cnt[v]++`.
2. After processing T, propagate counts up the Failure Tree (from leaves to root).
3. The total occurrences for a pattern ending at node 'u' is the sum of `cnt` in its subtree in the Failure Tree.

[APPLICATION 2: STRING DP (LEXICOGRAPHICAL/COUNTING)]
"Count strings of length L that do not contain any of the patterns."
- dp[i][u]: number of strings of length 'i' ending at Aho node 'u'.
- For each node 'u' and char 'c', if `!has_pattern(C[u][c])`, then `dp[i+1][C[u][c]] += dp[i][u]`.
- `has_pattern(v)` is true if `ted[v] > 0` or `has_pattern(F[v])` is true.

[APPLICATION 3: FINDING THE SHORTEST STRING CONTAINING ALL PATTERNS]
- Use BFS on the state (Aho_node, mask_of_patterns_found).
- `(v, mask) -> (C[v][i], mask | pattern_at[C[v][i]])`.

[SOLVING STRATEGY]
- Failure Tree: A node 'u' is a suffix of all nodes in its subtree in the Failure Tree.
- If you need to check if a node 'v' "contains" any pattern, precalculate `bad[v] = ted[v] | bad[F[v]]` during the BFS `BuildAho`.
- For multiple queries on a fixed set of patterns, use the Failure Tree + DFS order (tin/tout) + Fenwick tree to count occurrences of patterns in a text online.

[CODE: APPLICATIONS]
// 1. Counting occurrences in Text T
void count_occ(string &t) {
    int v = 0;
    for (char c : t) {
        v = C[v][c - 'a'];
        occ[v]++;
    }
    // Propagate up failure tree (reverse BFS order)
    for (int i = R - 1; i >= 0; i--) {
        int u = Q[i];
        occ[F[u]] += occ[u];
    }
}

// 2. String DP: Count strings of len L with NO patterns
ll dp[105][N]; // N is max nodes
ll solve_dp(int L) {
    // Precompute bad nodes
    for (int i = 0; i < R; i++) {
        int u = Q[i];
        bad[u] |= bad[F[u]];
    }
    dp[0][0] = 1;
    for (int i = 0; i < L; i++) {
        for (int v = 0; v <= ts; v++) {
            if (bad[v]) continue;
            for (int c = 0; c < 26; c++) {
                int next_v = C[v][c];
                if (!bad[next_v]) 
                    dp[i+1][next_v] = (dp[i+1][next_v] + dp[i][v]) % MOD;
            }
        }
    }
    ll total = 0;
    for (int v = 0; v <= ts; v++) total = (total + dp[L][v]) % MOD;
    return total;
}

// 3. Failure Tree Adjacency List (already in your snippet)
// void build_tree() {
//     for (int i = 1; i <= ts; i++) adj[F[i]].push_back(i);
// }