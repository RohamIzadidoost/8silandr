=== GAMES ON GRAPHS (RETROGRADE ANALYSIS) ===

[EXPLANATION]
In games on a directed graph, we classify nodes as WINNING, LOSING, or DRAW.
1. LOSING: A node with no outgoing edges (terminal) or where all moves lead to WINNING nodes.
2. WINNING: A node from which there is at least one move to a LOSING node.
3. DRAW: Nodes that can never be classified as WIN or LOSE (usually part of a cycle).

[USE CASES]
- Games with cycles where "forever" play results in a draw.
- Solving state-based games where states are nodes and moves are edges.
- Determining game outcomes in O(V + E) time.

[SOLVING STRATEGY]
1. Use reverse edges (radj) to propagate state changes backward.
2. Maintain 'deg[u]', the number of outgoing edges from node 'u'.
3. Use a queue 'q' to process determined nodes (starting with terminal nodes).
4. If a node 'v' is LOSING, all 'u' such that u->v become WINNING.
5. If a node 'v' is WINNING, decrement 'deg[u]' for all u->v. If 'deg[u]' becomes 0, 'u' becomes LOSING.
6. After processing, any node with 'res == 0' is a DRAW.

[CODE]
const int N = 2e5 + 5;
vector<int> adj[N], radj[N];
int deg[N], res[N], vis[N];

void solve(int n) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            res[i] = -1; // -1: Lose, 1: Win, 0: Draw
            q.push(i);
        }
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : radj[v]) {
            if (res[u] != 0) continue;
            if (res[v] == -1) {
                res[u] = 1;
                q.push(u);
            } else if (--deg[u] == 0) {
                res[u] = -1;
                q.push(u);
            }
        }
    }
}

void clr(int n) {
    for (int i = 0; i <= n; i++) {
        adj[i].clear(); radj[i].clear();
        deg[i] = res[i] = vis[i] = 0;
    }
}

---

=== SPRAGUE-GRUNDY THEOREM & NIM ===

[EXPLANATION]
1. Nim-Sum: In Nim, the winning strategy is to maintain a XOR sum of piles equal to 0. A state is LOSING if its Nim-sum is 0, otherwise WINNING.
2. Sprague-Grundy: Any impartial game (same moves for both players) is equivalent to a Nim pile of size G(s).
3. G(s) = MEX({G(s') | s -> s'}), where s' are states reachable from s in one move.
4. If a game consists of independent subgames, the total Grundy value is G = G(s1) ^ G(s2) ^ ... ^ G(sk).

[USE CASES]
- Games that can be decomposed into independent components (e.g., several piles, multiple pieces on a board).
- Standard Nim variations (Staircase Nim, Nim with restricted moves).
- Green Hackenbush on trees (G(v) = XOR sum of (G(child) + 1)).

[SOLVING STRATEGY]
1. If the game is a DAG, use DP/Memoization to calculate G(s) using the MEX of successors.
2. If the game is Nim, simply XOR all pile sizes.
3. For "Staircase Nim": Only piles on odd-numbered steps matter; the game is equivalent to Nim on those piles.
4. For games with large states, look for a pattern in G(n) values (e.g., periodic or linear).

[CODE]
const int N = 1e5 + 5;
int g[N];

int get_mex(set<int>& s) {
    int m = 0;
    while (s.count(m)) m++;
    return m;
}

// For a game like "Take 1, 3, or 4 items"
void calc_g(int n) {
    g[0] = 0;
    int moves[] = {1, 3, 4};
    for (int i = 1; i <= n; i++) {
        set<int> s;
        for (int m : moves) {
            if (i - m >= 0) s.insert(g[i - m]);
        }
        g[i] = get_mex(s);
    }
}

// XOR sum for multiple independent games
int solve_nim(vector<int>& piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    return x != 0; // 1 if Win, 0 if Lose
}

void clr(int n) {
    for (int i = 0; i <= n; i++) g[i] = 0;
}