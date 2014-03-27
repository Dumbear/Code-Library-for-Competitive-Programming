double get_distance(const point& p, const point& p1, const point& p2) {
    return abs((p1 - p) * (p2 - p) / (p1 - p2).len());
}

point get_perpendicular(const point& p, const point& p1, const point& p2) {
    double d = (p1 - p) * (p2 - p) / (p1 - p2).len();
    return p - (p2 - p1).rotate_left().trunc(d);
}

point get_reflection(const point& p, const point& p1, const point& p2) {
    double d = (p1 - p) * (p2 - p) / (p1 - p2).len();
    return p - (p2 - p1).rotate_left().trunc(d * 2.0);
}
