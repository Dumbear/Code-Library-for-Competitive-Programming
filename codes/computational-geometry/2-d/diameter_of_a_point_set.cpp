double get_max_distance(point* p, int n, point* pol, int& m) {
    get_convex_hull(p, n, pol, m);
    double dis = 0;
    for (int i = 0, j = dn - 1; i < m; ++i) {
        dis = max(dis, (pol[j] - pol[i]).len());
        while (sgn((pol[(i + 1) % m] - pol[i]) * (pol[(j + 1) % m] - pol[j])) > 0) {
            j = (j + 1) % m;
            dis = max(dis, (pol[j] - pol[i]).len());
        }
    }
    return dis;
}
