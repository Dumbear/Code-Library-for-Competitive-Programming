bool is_prime[max_n];
vector<int> primes;

void compute_primes() {
    fill(is_prime, is_prime + max_n, true);
    is_prime[0] = is_prime[1] = false;
    primes.clear();
    for (int i = 2; i < max_n; ++i) {
        if (is_prime[i])
            primes.push_back(i);
        for (vector<int>::iterator j = primes.begin(); j != primes.end() && i * *j < max_n; ++j) {
            is_prime[i * *j] = false;
            if (i % *j == 0)
                break;
        }
    }
}
