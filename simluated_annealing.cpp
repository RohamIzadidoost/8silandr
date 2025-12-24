=== SIMULATED ANNEALING ===

[SOLVING STRATEGY]
1. Start with a random state and a high Temperature (T).
2. Randomly modify the state (swap, move, etc.).
3. If the new state is better, accept it.
4. If it's worse, accept it with probability: exp((old_val - new_val) / T).
5. Gradually decrease T (Cooling).

[CODE]
double T = 1e6, cooling = 0.9999;
auto get_val = [&]() { /* Calculate cost */ };
while (T > 1e-9) {
    // 1. Modify state
    double cur = get_val();
    if (cur < best || exp((best - cur) / T) > (double)rand() / RAND_MAX) {
        best = cur;
    } else { /* Rollback */ }
    T *= cooling;
    if (clock() / (double)CLOCKS_PER_SEC > 1.9) break; // Time safety
}