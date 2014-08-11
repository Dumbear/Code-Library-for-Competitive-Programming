struct disjoint_set {
    int p[max_n];
    void clear(int n) {
        for (int i = 0; i < n; ++i)
            p[i] = i;
    }
    int get_root(int k) {
        return (p[k] == k ? k : p[k] = get_root(p[k]));
    }
    bool merge(int a, int b) {
        int r1 = get_root(a), r2 = get_root(b);
        if (r1 == r2)
            return false;
        p[r2] = r1;
        return true;
    }
};
