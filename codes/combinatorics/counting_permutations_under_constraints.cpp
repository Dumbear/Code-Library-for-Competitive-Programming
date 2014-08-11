int dp[max_n][max_n];

int count_permutations(int n, const vector<int>& c, int mod) {
    dp[0][0] = 1;
    for (int i = 0; i + 1 < n; ++i) {
        if (c[i] == -1) {
            int sum = 0;
            for (int j = 0; j <= i + 1; ++j) {
                dp[i + 1][j] = sum;
                sum = (sum + dp[i][j]) % mod;
            }
        } else if (c[i] == 1) {
            int sum = 0;
            for (int j = i + 1; j >= 0; --j) {
                sum = (sum + dp[i][j]) % mod;
                dp[i + 1][j] = sum;
            }
        } else {
            int sum = accumulate(dp[i], dp[i] + i + 1, 0LL) % mod;
            for (int j = 0; j <= i + 1; ++j)
                dp[i + 1][j] = sum;
        }
    }
    return accumulate(dp[n - 1], dp[n - 1] + n, 0LL) % mod;
}
