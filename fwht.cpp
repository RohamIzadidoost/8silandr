void fwht(vector<int>& a, bool inv) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = a[i+j], v = a[i+len+j];
                a[i+j] = u + v;
                a[i+len+j] = u - v;
                if (inv) { a[i+j] /= 2; a[i+len+j] /= 2; }
            }
        }
    }
}
================================================================================
                    FFT & NTT APPLICATIONS FOR ICPC
================================================================================
[1. COMBINATORIAL COUNTING & GENERATING FUNCTIONS]
To find the number of ways to pick items that sum to X:
- Define P(x) = sum(x^{value_i}). 
- Picking K items with replacement: Result is coefficient of x^X in [P(x)]^K.
- Use Binary Exponentiation on the polynomial: O(N log N log K).
- Application: Knapsack-like problems where weights are small but K is large.

[2. STRING MATCHING WITH WILDCARDS]
Problem: Find all shifts of Pattern P in Text T where '?' matches anything.
- Logic: Match at shift 'i' if sum_{j=0}^{m-1} (T[i+j] - P[j])^2 * T[i+j] * P[j] == 0.
- Optimization: Expand (T-P)^2 * T * P = T^3*P - 2*T^2*P^2 + T*P^3.
- Steps:
    1. Reverse P.
    2. Compute 3 convolutions: (T^3 * P_rev), (T^2 * P^2_rev), (T * P^3_rev).
    3. Sum them at each index. If sum[k] == 0, shift k is a match.

[3. ALL-PAIRS DISTANCE / SUMS]
Problem: Given two sets A and B, find all possible values of (a + b) or (a - b).
- a + b: Set freq[a] = 1, freq[b] = 1. Conv(freqA, freqB) gives counts of all sums.
- a - b: Equivalent to a + (-b). Shift indices by a constant to handle negatives,
  or reverse freqB and use convolution (effectively freqA[i] * freqB_rev[n-j]).

[4. CHARACTER MATCHING AT ALL SHIFTS]
Problem: For every possible shift of S relative to T, count matching characters.
- For each char 'c' in alphabet:
    1. A[i] = (S[i] == 'c')
    2. B[i] = (T[i] == 'c')
    3. Reverse B.
    4. C_c = A * B.
- Total matches at shift k = sum over all 'c' of C_c[k].

[5. SIGNAL PROCESSING: CROSS-CORRELATION]
To find the "best" alignment between two sequences (maximizing dot product):
- dot_product(shift k) = sum(A[i] * B[i+k]).
- This is exactly what convolution provides when one array is reversed.

[6. ADVANCED POLYNOMIAL OPS (O(N log N))]
- Polynomial Inverse: Solve A(x)B(x) = 1 mod x^n. (Used for Division).
- Polynomial Log/Exp: Used for counting labeled structures (e.g., number of 
  connected graphs with N nodes).
- Square Root: Find B(x) such that B(x)^2 = A(x).

[7. PRECISION TRICK: 3-MOD CRT]
If the modulo is not NTT-friendly or coefficients exceed 10^9:
- Run NTT under 3 different modulos: 998244353, 1004535809, 469762049.
- Use Chinese Remainder Theorem (CRT) to combine results into a 64-bit integer.

[8. BITWISE CONVOLUTIONS (FWHT)]
- XOR Convolution: C[i ^ j] = sum(A[i] * B[j]).
- AND Convolution: C[i & j] = sum(A[i] * B[j]).
- OR Convolution:  C[i | j] = sum(A[i] * B[j]).
Uses Fast Walsh-Hadamard Transform (O(N log N)).

================================================================================