bool get_intersection(const point& p1, const point& p2, const point& pl1, const point& pl2, const point& pl3, point& c) {
    point v = (pl2 - pl1) * (pl3 - pl1);
    double d1 = v ^ (p1 - pl1), d2 = v ^ (p2 - pl1);
    int s1 = sgn(d1), s2 = sgn(d2);
    if (s1 == 0 && s2 == 0)
        return false;
    c = point((p1.x * d2 - p2.x * d1) / (d2 - d1), (p1.y * d2 - p2.y * d1) / (d2 - d1), (p1.z * d2 - p2.z * d1) / (d2 - d1));
    return s1 * s2 <= 0;
}
