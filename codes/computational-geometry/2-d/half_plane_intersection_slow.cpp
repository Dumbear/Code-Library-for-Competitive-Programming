void get_intersection(point* pol1, int n1, const point& p1, const point& p2, point* pol2, int& n2) {
    n2 = 0;
    if (n1 == 0)
        return;
    point v = p2 - p1;
    int last_s = sgn(v * (pol1[n1 - 1] - p1));
    for (int i = 0; i < n1; ++i) {
        int s = sgn(v * (pol1[i] - p1));
        if (s == 0) {
            pol2[n2++] = pol1[i];
        } else if (s < 0) {
            if (last_s > 0)
                pol2[n2++] = get_intersection(p1, p2, i == 0 ? pol1[n1 - 1] : pol1[i - 1], pol1[i]);
        } else if (s > 0) {
            if (last_s < 0)
                pol2[n2++] = get_intersection(p1, p2, i == 0 ? pol1[n1 - 1] : pol1[i - 1], pol1[i]);
            pol2[n2++] = pol1[i];
        }
        last_s = s;
    }
}
