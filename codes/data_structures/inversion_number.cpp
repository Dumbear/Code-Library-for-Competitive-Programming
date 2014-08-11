binary_indexed_tree bit;

int get_inversion_number(const int* first, const int* last) {
    int res = 0;
    vector<int> dict(first, last);
    sort(dict.begin(), dict.end(), greater<int>());
    dict.resize(unique(dict.begin(), dict.end()) - dict.begin());
    bit.clear(dict.size());
    for (; first != last; ++first) {
        int index = lower_bound(dict.begin(), dict.end(), *first, greater<int>()) - dict.begin();
        bit.add(index + 1, 1);
        res += bit.get_sum(index);
    }
    return res;
}
