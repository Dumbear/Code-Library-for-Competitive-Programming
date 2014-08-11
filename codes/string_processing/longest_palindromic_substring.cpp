int ext[max_n * 2];

pair<int, int> longest_palindromic_substring(const char* x) {
    string s("\x81");
    for (int i = 0; x[i] != '\0'; ++i) {
        s += '\x80';
        s += x[i];
    }
    s += "\x80\x82";
    pair<int, int> res(0, -1);
    for (int i = 1, id = 0; i + 1 < s.size(); ++i) {
        ext[i] = (id + ext[id] > i ? min(ext[2 * id - i], id + ext[id] - i) : 1);
        for (; s[i + ext[i]] == s[i - ext[i]]; ++ext[i]);
        if (i + ext[i] > id + ext[id])
            id = i;
        if (ext[i] - 1 > res.first)
            res = make_pair(ext[i] - 1, i);
    }
    return res;
}
