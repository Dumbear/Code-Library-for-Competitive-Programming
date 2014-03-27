double get_distance(const point& p, const point& p1, const point& p2) {
    return abs(((p1 - p) * (p2 - p)).len() / (p1 - p2).len());
}

point get_perpendicular(const point& p, const point& p1, const point& p2) {
    point v = (p1 - p) * (p2 - p);
    double d = v.len() / (p1 - p2).len();
    return p - (v * (p2 - p1)).trunc(d);
}

point get_reflection(const point& p, const point& p1, const point& p2) {
    point v = (p1 - p) * (p2 - p);
    double d = v.len() / (p1 - p2).len();
    return p - (v * (p2 - p1)).trunc(d * 2.0);
}
