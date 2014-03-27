struct convex_hull {
    map<int, int> hd, hu;
    bool add(const point& p, bool is_test = false) {
        bool f = false;
        f |= add(hd, p, +1, is_test);
        f |= add(hu, p, -1, is_test);
        return f;
    }
    bool add(map<int, int>& h, const point& p, int s, bool is_test) {
        map<int, int>::iterator it = h.find(p.x);
        if (it != h.end()) {
            if ((p.y - it->second) * s >= 0)
                return false;
            if (is_test)
                return true;
            h.erase(it);
        }
        it = h.insert(make_pair(p.x, p.y)).first;
        if (is_bad(h, it, s)) {
            h.erase(it);
            return false;
        }
        if (is_test) {
            h.erase(it);
            return true;
        }
        for (map<int, int>::iterator i = it; i != h.begin() && is_bad(h, --i, s); i = it)
            h.erase(i);
        for (map<int, int>::iterator i = it; i != --h.end() && is_bad(h, ++i, s); i = it)
            h.erase(i);
        return true;
    }
    bool is_bad(const map<int, int>& h, const map<int, int>::iterator& it, int s) {
        if (it == h.begin() || it == --h.end())
            return false;
        return get_position(h, it) * s >= 0;
    }
    int get_position(const map<int, int>& h, const map<int, int>::iterator& it) {
        map<int, int>::iterator it1 = it, it2 = it;
        point p(*it), p1(*--it1), p2(*++it2);
        long long s = (p1 - p) * (p2 - p);
        return s > 0 ? 1 : (s < 0 ? -1 : 0);
    }
    bool contains(const point& p) {
        return !add(p, true);
    }
};
