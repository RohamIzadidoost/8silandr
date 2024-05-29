#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long m, c;
    Line(long long _m = 0ll, long long _c = 0ll) {m = (long long)_m; c = (long long)_c;}
    long long find_y (int x) { return (m * (long long)(x)) + c;}
    long double intersect_x (Line l) {return (long double)(l.c - c) / (long double)(m - l.m); }
};
deque < Line > dq;

const int MAXN = 1e6 + 12;
int n, p[MAXN], q[MAXN];
long long dp[MAXN], ans, a[MAXN];
vector < int > points;

int32_t main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> q[i] >> a[i];
        points.push_back(i);
    }
    sort(points.begin(), points.end(), cmp);

    dq.push_back(Line(0, 0));
    for (int i = 0; i < n; i++) {
        int ind = points[i];
        while(dq.size() >= 2
            && dq.back().find_y(q[ind]) <= dq[dq.size() - 2].find_y(q[ind]))
            dq.pop_back();

        dp[i] = ((long long)(p[ind]) * (long long)(q[ind])) - (long long)a[ind] + dq.back().find_y(q[ind]);
        Line new_line(-1ll * p[ind], (long long)(dp[i]));

        while (dq.size() >= 2
            && dq[0].intersect_x(new_line) >= dq[0].intersect_x(dq[1]))
            dq.pop_front();
        dq.push_front(new_line);
        ans = max(ans, dp[i]);
    }

    cout << ans;
    return 0;
}
