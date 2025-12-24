struct Node {
    long long sum;
    long long max_val;
    Node() {
        sum = 0;
        max_val = -1e18;
    }
    Node(int val) {
        sum = val;
        max_val = val;
    }
};
Node merge(const Node& left, const Node& right) {
    Node res;
    res.sum = left.sum + right.sum;
    res.max_val = max(left.max_val, right.max_val);
    return res;
}
struct SegmentTree {
    int n;
    vector<Node> tree;
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }
    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = Node(a[start]);
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }
    void build(const vector<int>& a) {
        build(a, 1, 0, n - 1);
    }
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = Node(val);
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }
    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        Node p1 = query(2 * node, start, mid, l, r);
        Node p2 = query(2 * node + 1, mid + 1, end, l, r);
        return merge(p1, p2);
    }
};
