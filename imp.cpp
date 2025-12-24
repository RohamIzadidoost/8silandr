#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    // --- 1. scanf & printf ---
    int i; long long ll; char c; char s[100]; double d;
    // Aggregated Input: Int, LongLong, Char, String, Double
    scanf("%d %lld %c %s %lf", &i, &ll, &c, s, &d);
    // Formatted Output
    printf("%.4lf\n", d);      // Precision (3.1416)
    printf("%05d\n", i);       // Zero padding (00042)
    printf("%-5d|\n", i);      // Left align (42   |)
    // --- 2. Input Until EOF (Two Methods) ---
    int n;
    while (cin >> n) {}
    // Method B: Using scanf
    while (scanf("%d", &n) != EOF) {}
    // --- 3. String Parsing ---
    // Get full line (including spaces)
    string line;
    getline(cin, line); 
    // Split string (Tokenize)
    stringstream ss(line);
    string word;
    while (ss >> word) {// 'word' is the next token}
    // Trim (Manually removing whitespace)
    const string WS = " \n\r\t\f\v";
    size_t start = line.find_first_not_of(WS);
    line = (start == string::npos) ? "" : line.substr(start); // Left Trim
    size_t end = line.find_last_not_of(WS);
    line = (end == string::npos) ? "" : line.substr(0, end + 1); // Right Trim
    return 0;
}
