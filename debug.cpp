#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

int main() {
    // Example: Generate a random tree with N nodes
    int n = rnd(2, 10); // Small N to make manual debugging easier
    printf("%d\n", n);
    for (int i = 2; i <= n; i++) {
        printf("%d %d\n", rnd(1, i - 1), i);
    }
}

# Compile everything
g++ -O3 sol.cpp -o sol
g++ -O3 ref.cpp -o ref
g++ -O3 gen.cpp -o gen

for ((i = 1; ; ++i)); do
    ./gen > in
    ./sol < in > out_sol
    ./ref < in > out_ref
    
    if diff -Z out_sol out_ref > /dev/null; then
        echo "Passed Test $i"
    else
        echo "FAILED Test $i!"
        echo "Input:"
        cat in
        echo "Your Output:"
        cat out_sol
        echo "Correct Output:"
        cat out_ref
        break
    fi
done
