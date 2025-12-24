=== MÖBIUS INVERSION & NUMBER THEORY ===

[EXPLANATION]
1. Möbius Function (μ(n)):
   - μ(1) = 1.
   - μ(n) = 0 if n is divisible by any prime squared (p^2 | n).
   - μ(n) = (-1)^k if n is a product of k distinct primes.
2. Möbius Inversion Formula:
   If f(n) = sum_{d|n} g(d), then g(n) = sum_{d|n} μ(d) * f(n/d).
3. Fundamental Property:
   sum_{d|gcd(i, j)} μ(d) = [gcd(i, j) == 1]. This is the "sieve" that converts GCD constraints into sums.

[USE CASES]
- Counting pairs (i, j) with 1 <= i <= N, 1 <= j <= M such that gcd(i, j) = K.
- Evaluating sums like sum_{i=1 to N} sum_{j=1 to M} gcd(i, j).
- Problems involving "square-free" numbers or counts of coprime elements.

[SOLVING STRATEGY]
1. Compute μ(n) using a Linear Sieve in O(N).
2. Rewrite the problem to isolate the GCD:
   - To count pairs with gcd(i, j) = K, it is equivalent to counting pairs (i', j') with 1 <= i' <= N/K, 1 <= j' <= M/K such that gcd(i', j') = 1.
   - Use the property: sum_{i=1 to N} sum_{j=1 to M} [gcd(i, j)=1] = sum_{d=1 to min(N, M)} μ(d) * floor(N/d) * floor(M/d).
3. Optimization: For multiple queries or large N, use Block Decomposition (Square Root Trick) on floor(N/d) and floor(M/d) to answer in O(sqrt(N)).

[CODE]
const int N = 1e6 + 5;
int p[N], mu[N], vis[N], smu[N], cnt;

void sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            p[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i * p[j] <= n; j++) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) {
                mu[i * p[j]] = 0;
                break;
            }
            mu[i * p[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) smu[i] = smu[i - 1] + mu[i];
}

// O(sqrt(N)) query: Count pairs (i, j) with 1 <= i <= n, 1 <= j <= m and gcd(i, j) == 1
ll qry(int n, int m) {
    ll res = 0;
    int lim = min(n, m);
    for (int l = 1, r; l <= lim; l = r + 1) {
        r = min({lim, n / (n / l), m / (m / l)});
        res += (ll)(smu[r] - smu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}

void clr(int n) {
    cnt = 0;
    for (int i = 0; i <= n; i++) vis[i] = mu[i] = smu[i] = 0;
}