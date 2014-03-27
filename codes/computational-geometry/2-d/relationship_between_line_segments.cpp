bool get_intersection(const point& p1, const point& p2, const point& p3, const point& p4, point& c) {
    double d1 = (p2 - p1) * (p3 - p1), d2 = (p2 - p1) * (p4 - p1);
    double d3 = (p4 - p3) * (p1 - p3), d4 = (p4 - p3) * (p2 - p3);
    int s1 = sgn(d1), s2 = sgn(d2), s3 = sgn(d3), s4 = sgn(d4);
    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0)
        return false;
    c = (p3 * d2 - p4 * d1) / (d2 - d1);
    return s1 * s2 <= 0 && s3 * s4 <= 0;
}
