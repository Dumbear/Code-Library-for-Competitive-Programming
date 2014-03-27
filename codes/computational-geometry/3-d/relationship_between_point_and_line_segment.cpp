double get_distance(const point& p, const point& p1, const point& p2) {
    if (sgn((p2 - p1) ^ (p - p1)) <= 0)
        return (p - p1).len();
    if (sgn((p1 - p2) ^ (p - p2)) <= 0)
        return (p - p2).len();
    return abs(((p1 - p) * (p2 - p)).len() / (p1 - p2).len());
}
