double get_distance(const point& p1, const point& p2, const point& p3, const point& p4) {
    point n = (p2 - p1) * (p4 - p3);
    if (sgn(n.len()) == 0)
        return get_distance(p1, p3, p4);
    return abs((p3 - p1) ^ n / n.len());
}
