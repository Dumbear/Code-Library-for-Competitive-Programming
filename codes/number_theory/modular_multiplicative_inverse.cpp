long long inv[max_n];

void compute_inverses(int mod) {
    inv[1] = 1;
    for (int i = 2; i < max_n; ++i)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

long long get_inverse(long long num, int mod) {
    long long inv = 1;
    for (int i = mod - 2; i != 0; i >>= 1) {
        if ((i & 1) == 1)
            inv = inv * num % mod;
        num = num * num % mod;
    }
    return inv;
}
