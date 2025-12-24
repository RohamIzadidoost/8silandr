=== MANACHER'S ALGORITHM ===

[EXPLANATION]
Manacher's algorithm finds all palindromic substrings in a string in O(N). It computes two arrays:
1. d1[i]: The number of odd-length palindromes centered at index i (radius including the center).
2. d2[i]: The number of even-length palindromes centered at index i (specifically, the palindrome consists of s[i-k...i+k-1]).

[USE CASES]
- Finding the Longest Palindromic Substring (LPS).
- Counting the total number of palindromic substrings.
- O(1) Palindrome Queries: Checking if any substring s[L...R] is a palindrome.
- Solving problems involving "palindromic tree" logic when the tree is overkill.

[SOLVING STRATEGY]
1. Build d1 and d2. To find the longest palindrome:
   - For odd: len = 2 * d1[i] - 1.
   - For even: len = 2 * d2[i].
2. Total palindromes: sum(d1[i]) + sum(d2[i]).
3. Substring s[L...R] is a palindrome if:
   - len = R - L + 1.
   - If len is odd: d1[(L+R)/2] >= (len+1)/2.
   - If len is even: d2[(L+R+1)/2] >= len/2.

[CODE]
const int N = 1e6 + 5;
int d1[N], d2[N];

void manacher(string s) {
    int n = s.size();
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
}

void clr(int n) {
    for (int i = 0; i <= n; i++) d1[i] = d2[i] = 0;
}