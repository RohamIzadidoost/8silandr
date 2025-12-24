ll n , p[maxn] , h[lg][maxn] , sa[maxn] , lcp[maxn] , mark[maxn] , ps[maxn] , l[maxn] , r[maxn] , cp , ans ; 
string s , t ; 
stack<int> st ; 
bool cmp(int i , int j){
	if(h[cp-1][i] < h[cp-1][j]) return true; 
	if(h[cp-1][i] > h[cp-1][j]) return false ; 
	if(i + (1 << (cp-1)) > n + 1 || j + (1 << (cp-1)) > n + 1) return i < j ;  
	return h[cp-1][i + (1 << (cp-1))] < h[cp-1][j + (1 << (cp-1))] ; 
}
void SA(){
	for(int i = 1 ; i <= n ; i ++ ) p[i] = i , h[0][i] = s[i]; 
	for(cp = 1 ; cp < lg ; cp++ ){
		sort(p +1 , p + n + 1 , cmp) ; 
		h[cp][p[1]] =1 ; 
		for(int i = 2 ; i <= n ; i ++ ) h[cp][p[i]] = h[cp][p[i-1]] + cmp(p[i-1] , p[i]) ; 
	}
}
void Lcp(){
	for(int i = 1 , k = 0 ; i <= n ; i ++ ){
		if(sa[i] == n) continue ; 
		for(int j = p[sa[i] + 1] ; k <= n && s[i+k] == s[j+k] ; ) k++ ; 
		lcp[sa[i]] = k ; 
		if(k) k -- ; 
	}
}

=== SUFFIX ARRAY APPLICATIONS ===

[APPLICATION 1: DISTINCT SUBSTRINGS]
Total substrings is N*(N+1)/2. Each LCP[i] represents a prefix that was already counted in the previous suffix in sorted order.
Formula: Ans = [N*(N+1)/2] - sum(LCP[i] for i from 1 to N-1)

[APPLICATION 2: LONGEST COMMON SUBSTRING (LCS) OF TWO STRINGS]
Concatenate S and T with a unique separator: S + '#' + T. Build SA and LCP.
The LCS is the maximum LCP[i] such that sa[i] and sa[i+1] belong to different strings.
- S: indices [1, |S|]
- T: indices [|S|+2, |S|+|T|+1]

[APPLICATION 3: STRING MATCHING / RANGE OF OCCURRENCES]
Since suffixes are sorted, all occurrences of a pattern P appear as a contiguous range [L, R] in the SA. 
Use binary search twice to find the first and last suffix starting with P.

[SOLVING STRATEGY]
- For #2 (LCS), check if (sa[i] <= n1 && sa[i+1] > n1+1) or vice versa.
- For "Longest Repeated Substring", it is simply the max value in the LCP array.
- For "K-th Lexicographical Substring", iterate through SA; suffix sa[i] contributes (n - sa[i] + 1 - LCP[i-1]) new substrings.

[CODE: APPLICATIONS]
// 1. Distinct Substrings
ll count_distinct(int n, ll lcp[]) {
    ll res = (ll)n * (n + 1) / 2;
    for (int i = 1; i < n; i++) res -= lcp[i];
    return res;
}

// 2. Longest Common Substring (LCS)
// S = S1 + '#' + S2; n1 = S1.size();
int longest_common(int n, int n1, ll sa[], ll lcp[]) {
    int mx = 0;
    for (int i = 1; i < n; i++) {
        bool in1 = (sa[i] <= n1), next_in2 = (sa[i+1] > n1 + 1);
        bool in2 = (sa[i] > n1 + 1), next_in1 = (sa[i+1] <= n1);
        if ((in1 && next_in2) || (in2 && next_in1)) {
            mx = max(mx, (int)lcp[i]);
        }
    }
    return mx;
}

// 3. Pattern Matching (Find Range [L, R])
pair<int, int> find_pattern(string &p, string &s, int n, ll sa[]) {
    int m = p.size();
    int L = 1, R = n, first = -1, last = -1;
    // Lower bound
    while (L <= R) {
        int mid = (L + R) / 2;
        if (s.substr(sa[mid], m) >= p) {
            first = mid; R = mid - 1;
        } else L = mid + 1;
    }
    // Upper bound
    L = 1, R = n;
    while (L <= R) {
        int mid = (L + R) / 2;
        if (s.substr(sa[mid], m) <= p) {
            last = mid; L = mid + 1;
        } else R = mid - 1;
    }
    if (first != -1 && s.substr(sa[first], m) != p) return {-1, -1};
    return {first, last};
}

// 4. Most Frequent Substring of length K
// Use a sliding window or frequency map on the SA range where LCP >= K.

=== LCS OF K STRINGS (SA + SLIDING WINDOW) ===

[EXPLANATION]
1. Concatenate all K strings using unique separators: S1 + #1 + S2 + #2 + ... + SK.
2. Build the Suffix Array (SA) and LCP array for the combined string.
3. Use a sliding window [L, R] on the SA that contains at least one suffix from each of the K original strings.
4. For each such window, the common prefix length is min(LCP[L...R-1]). 
5. The global maximum of these minimums is the LCS.

[USE CASES]
- Finding the longest substring present in all K strings.
- Finding the longest substring present in at least M out of K strings (variation of the window).

[SOLVING STRATEGY]
1. Assign an ID to each character in the concatenated string to identify which original string it belongs to.
2. Use a frequency array and a 'count' variable to track how many unique strings are in the current window [L, R].
3. Use a Deque (monotonic queue) to find the minimum LCP in the window [L, R] in O(1) amortized.
4. Total Complexity: O(N log N) for SA + O(N) for sliding window.

[CODE]
const int N = 1e6 + 5;
int id[N], cnt[N], unique_strings;
int q[N], head, tail; // Monotonic queue for range min LCP

// n: total length, k: number of strings
int solve_lcs(int n, int k, int sa[], int lcp[]) {
    int L = 1, total_found = 0, mx = 0;
    head = 0; tail = 0;
    
    for (int R = 1; R <= n; R++) {
        // Add sa[R] to window
        if (id[sa[R]] != 0) { // Not a separator
            if (cnt[id[sa[R]]] == 0) total_found++;
            cnt[id[sa[R]]]++;
        }
        
        // Maintain monotonic queue for LCP min in [L, R-1]
        if (R > 1) {
            while (head < tail && lcp[q[tail - 1]] >= lcp[R - 1]) tail--;
            q[tail++] = R - 1;
        }

        // Shrink window
        while (total_found == k) {
            // Update answer: min LCP in [L, R-1]
            if (head < tail) mx = max(mx, lcp[q[head]]);
            
            int left_id = id[sa[L]];
            if (left_id != 0) {
                cnt[left_id]--;
                if (cnt[left_id] == 0) total_found--;
            }
            L++;
            while (head < tail && q[head] < L) head++;
        }
    }
    return mx;
}

void clr(int n) {
    for (int i = 0; i <= n; i++) id[i] = cnt[i] = 0;
}