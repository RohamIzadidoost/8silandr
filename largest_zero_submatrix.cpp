=== LARGEST ZERO SUBMATRIX ===

[EXPLANATION]
Given a binary matrix, we want to find the submatrix (rectangle) with the maximum area consisting only of zeros. This is solved by transforming the 2D grid into a "Largest Rectangle in Histogram" problem for each row. 
For a fixed row $i$, let $h[j]$ be the number of consecutive zeros in column $j$ ending at row $i$. We iterate through rows, update $h[j]$, and solve the histogram problem in $O(M)$ using a monotonic stack.

[USE CASES]
- Finding the largest empty rectangular area in a grid with obstacles.
- Maximizing profit in a 2D layout where certain cells are blocked.
- Base logic for "Number of submatrices with property P" problems.

[SOLVING STRATEGY]
1. Maintain an array $h[M]$ where $h[j]$ is the height of consecutive zeros at column $j$.
2. For each row:
   - If $mat[i][j] == 0$, $h[j]++$; else $h[j] = 0$.
   - Use a monotonic stack to find $L[j]$ and $R[j]$, the nearest columns to the left and right with height strictly less than $h[j]$.
   - The area for column $j$ is $h[j] \times (R[j] - L[j] - 1)$.
3. Total Complexity: $O(N \times M)$.
4. To count *all* zero submatrices: Instead of max area, use $dp[j] = h[j] \times (j - L[j]) + dp[L[j]]$. The sum of $dp[j]$ across all cells is the total count.

[CODE]
const int N = 1005;
int h[N], L[N], R[N], st[N], n, m;
long long dp[N];

long long solve_area() {
    long long mx = 0;
    int top = 0;
    for (int i = 0; i < m; i++) {
        while (top > 0 && h[st[top - 1]] >= h[i]) top--;
        L[i] = (top == 0 ? -1 : st[top - 1]);
        st[top++] = i;
    }
    top = 0;
    for (int i = m - 1; i >= 0; i--) {
        while (top > 0 && h[st[top - 1]] >= h[i]) top--;
        R[i] = (top == 0 ? m : st[top - 1]);
        st[top++] = i;
    }
    for (int i = 0; i < m; i++) 
        mx = max(mx, (long long)h[i] * (R[i] - L[i] - 1));
    return mx;
}

long long count_all() {
    long long tot = 0;
    int top = 0;
    for (int i = 0; i < m; i++) {
        while (top > 0 && h[st[top - 1]] >= h[i]) top--;
        int left = (top == 0 ? -1 : st[top - 1]);
        if (left == -1) dp[i] = (long long)h[i] * (i + 1);
        else dp[i] = (long long)h[i] * (i - left) + dp[left];
        st[top++] = i;
        tot += dp[i];
    }
    return tot;
}

void clr() {
    for (int i = 0; i <= m; i++) h[i] = dp[i] = 0;
}

/* Usage inside row loop:
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (a[i][j] == 0) h[j]++;
        else h[j] = 0;
    }
    ans = max(ans, solve_area());
}
*/