int dn, hd[max_n], un, hu[max_n];

void get_convex_hull(point* p, int n, point* pol, int& m) {
    sort(p, p + n);
    dn = un = 2;
    hd[0] = hu[0] = 0;
    hd[1] = hu[1] = 1;
    for (int i = 2; i < n; ++i) {
        for (; dn > 1 && sgn((p[hd[dn - 1]] - p[hd[dn - 2]]) * (p[i] - p[hd[dn - 1]])) <= 0; --dn);
        for (; un > 1 && sgn((p[hu[un - 1]] - p[hu[un - 2]]) * (p[i] - p[hu[un - 1]])) >= 0; --un);
        hd[dn++] = hu[un++] = i;
    }
    m = 0;
    for (int i = 0; i < dn - 1; ++i)
        pol[m++] = p[hd[i]];
    for (int i = un - 1; i > 0; --i)
        pol[m++] = p[hu[i]];
}
