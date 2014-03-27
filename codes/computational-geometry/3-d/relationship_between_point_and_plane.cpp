double get_distance(const point& p, const point& p1, const point& p2, const point& p3) {
    point v = (p2 - p1) * (p3 - p1);
    return abs((v ^ (p - p1)) / v.len());
}

point get_perpendicular(const point& p, const point& p1, const point& p2, const point& p3) {
    point v = (p2 - p1) * (p3 - p1);
    double d = (v ^ (p - p1)) / v.len();
    return p - v.trunc(d);
}

point get_reflection(const point& p, const point& p1, const point& p2, const point& p3) {
    point v = (p2 - p1) * (p3 - p1);
    double d = (v ^ (p - p1)) / v.len();
    return p - v.trunc(d * 2.0);
}
