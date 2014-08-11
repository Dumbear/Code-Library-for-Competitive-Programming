struct binary_indexed_tree {
    int n, sum[max_n];
    void clear(int size) {
        n = size;
        fill(sum + 1, sum + 1 + n, 0);
    }
    void add(int pos, int val) {
        for (; pos <= n; pos += pos & -pos)
            sum[pos] += val;
    }
    int get_sum(int pos) const {
        int res = 0;
        for (; pos > 0; pos -= pos & -pos)
            res += sum[pos];
        return res;
    }
    int get_sum(int first, int last) const {
        return get_sum(last) - get_sum(first - 1);
    }
};
