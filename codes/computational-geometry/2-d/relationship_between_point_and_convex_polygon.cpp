int get_position(const point& p, const point* pol, int n) {
    point c((pol[n - 1].x + pol[0].x) / 2.0, (pol[n - 1].y + pol[0].y) / 2.0);
    int s = sgn((pol[0] - pol[n - 1]) * (p - pol[n - 1]));
    if (s < 0)
        return -1;
    if (s == 0)
        return sgn((p - pol[n - 1]) ^ (p - pol[0])) <= 0 ? 0 : -1;
    int lb = 0, ub = n - 1;
    while (lb != ub) {
        int mid = (lb + ub + 1) / 2;
        if (sgn((pol[mid] - c) * (p - c)) >= 0)
            lb = mid;
        else
            ub = mid - 1;
    }
    return sgn((pol[lb + 1] - pol[lb]) * (p - pol[lb]));
}
