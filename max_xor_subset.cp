=== XOR BASIS ===
ll basis[64];
void insert(ll x) {
    for (int i = 62; i >= 0; i--) {
        if (!(x >> i)) continue;
        if (!basis[i]) { basis[i] = x; return; }
        x ^= basis[i];
    }
}

// Maximum XOR sum possible from any subset
ll max_xor() {
    ll res = 0;
    for (int i = 62; i >= 0; i--) 
        if ((res ^ basis[i]) > res) res ^= basis[i];
    return res;
}