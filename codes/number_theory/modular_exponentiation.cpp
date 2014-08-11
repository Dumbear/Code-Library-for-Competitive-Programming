long long pow(long long x, long long y, int mod) {
    long long res = 1;
    for (x %= mod; y != 0; y >>= 1) {
        if ((y & 1) == 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
