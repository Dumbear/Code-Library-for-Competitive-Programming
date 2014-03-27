struct edge {
    int id;
    point v;
    double ang;
    edge() {
    }
    edge(int _id, const point& _v): id(_id), v(_v) {
        ang = atan2(v.y, v.x);
        if (sgn(ang - pi) == 0)
            ang = -pi;
    }
};

bool operator<(const edge& e1, const edge& e2) {
    return sgn(e1.ang - e2.ang) < 0;
}

edge e[max_n];
point l1, l2;

void pre_compute(point* pol, int n) {
    for (int i = 0; i < n; ++i) {
        pol[n + i] = pol[i];
        e[i] = edge(i, pol[i + 1] - pol[i]);
    }
    sort(e, e + n);
}

bool is_less(const point& p1, const point& p2) {
    return sgn((l1 - p1) * (l2 - p1) - (l1 - p2) * (l2 - p2)) < 0;
}

bool get_intersection(const point* pol, int n, const point& p1, const point& p2, point& c1, point& c2) {
    int p_l = e[(lower_bound(e, e + n, edge(-1, p1 - p2)) - e) % n].id;
    int p_r = e[(lower_bound(e, e + n, edge(-1, p2 - p1)) - e) % n].id;
    if (sgn((p2 - p1) * (pol[p_l] - p1)) * sgn((p2 - p1) * (pol[p_r] - p1)) >= 0)
        return false;
    l1 = p2, l2 = p1;
    int k1 = (lower_bound(pol + p_l, pol + (p_r < p_l ? p_r + n : p_r) + 1, p1, is_less) - pol) % n;
    l1 = p1, l2 = p2;
    int k2 = (lower_bound(pol + p_r, pol + (p_l < p_r ? p_l + n : p_l) + 1, p2, is_less) - pol) % n;
    c1 = get_intersection(p1, p2, pol[k1], pol[(k1 + n - 1) % n]);
    c2 = get_intersection(p1, p2, pol[k2], pol[(k2 + n - 1) % n]);
    return true;
}
