Dinic:
int from[MAXE], to[MAXE], cap[MAXE], prv[MAXE], head[MAXN], pt[MAXN], ec;
void addEdge(int u, int v, int uv, int vu = 0){
	from[ec] = u, to[ec] = v, cap[ec] = uv, prv[ec] = head[u], head[u] = ec++;
	from[ec] = v, to[ec] = u, cap[ec] = vu, prv[ec] = head[v], head[v] = ec++;
}
int lv[MAXN], q[MAXN];
bool bfs(int source, int sink){
	memset(lv, 63, sizeof(lv));
	int h = 0, t = 0;
	lv[source] = 0;
	q[t++] = source;
	while (t-h){
		int v = q[h++];
		for (int e = head[v]; ~e; e = prv[e])
			if (cap[e] && lv[v] + 1 < lv[to[e]]){
				lv[to[e]] = lv[v] + 1;
				q[t++] = to[e];
			}
	}
	return lv[sink] < 1e8;
}
int dfs(int v, int sink, int f = 1e9){
	if (v == sink || f == 0)
		return f;
	int ret = 0;
	for (int &e = pt[v]; ~e; e = prv[e])
		if (lv[v]+1 == lv[to[e]]){
			int x = dfs(to[e], sink, min(f, cap[e]));
			cap[e] -= x;
			cap[e^1] += x;
			ret += x;
			f -= x;
			if (!f)
				break;
		}
	return ret;
}
int dinic(int source, int sink){
	int ret = 0;
	while (bfs(source, sink)){
		memcpy(pt, head, sizeof(head));
		ret += dfs(source, sink);
	}
	return ret;
}

	memset(head, -1, sizeof(head));
//mohem

// 1. Get flow on a specific edge index 'e'
int get_flow(int e) {
    // If the edge was added as addEdge(u, v, uv, 0):
    return cap[e ^ 1]; 
}

// 2. Find Min-Cut Edges
vector<int> get_min_cut() {
    vector<int> cut_edges;
    // bfs(source, sink) must be called last to set lv[]
    for (int i = 0; i < ec; i += 2) { // Only check forward edges
        int u = from[i], v = to[i];
        if (lv[u] < 1e8 && lv[v] >= 1e8) {
            cut_edges.push_back(i);
        }
    }
    return cut_edges;
}

// 3. Bipartite Matching Recovery
void print_matching(int n_left) {
    for (int i = 0; i < ec; i += 2) {
        int u = from[i], v = to[i];
        // Assuming nodes 1..n_left are left side, others are right side
        // Filter out source (0) and sink (T) edges
        if (u >= 1 && u <= n_left && v > n_left && cap[i^1] > 0) {
            cout << u << " matched with " << v << endl;
        }
    }
}