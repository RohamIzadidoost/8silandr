[CODE]
#include <queue>
#include <vector>

// Standard Max-Heap
priority_queue<int> pq;

// Standard Min-Heap
priority_queue<int, vector<int>, greater<int>> min_pq;

// Custom Comparator for Struct
struct Node {
    int u, dist;
    bool operator<(const Node& o) const {
        return dist > o.dist; // Reversed for min-priority (useful in Dijkstra)
    }
};
priority_queue<Node> custom_pq;

// Fast build from existing vector
void build_fast(vector<int>& v) {
    priority_queue<int> fast_pq(v.begin(), v.end()); // O(N)
}