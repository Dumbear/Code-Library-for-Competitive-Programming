struct circle {
    point c;
    double r;
    circle() {
    }
    circle(const point& _c, double _r): c(_c), r(_r) {
    }
    void input() {
        c.input();
        scanf("%lf", &r);
    }
    double area() const {
        return pi * r * r;
    }
    int get_intersection(const point& p1, const point& p2, point& c1, point& c2) const {
        double d = (p1 - c) * (p2 - c) / (p1 - p2).len();
        if (sgn(abs(d) - r) >= 0)
            return 0;
        point pp = c - (p2 - p1).rotate_left().trunc(d);
        double l = sqrt(r * r - d * d);
        c1 = pp - (p2 - p1).trunc(l);
        c2 = pp + (p2 - p1).trunc(l);
        int res = 0;
        res |= (sgn((p1 - c1) ^ (p2 - c1)) <= 0 ? 1 : 0) << 0;
        res |= (sgn((p1 - c2) ^ (p2 - c2)) <= 0 ? 1 : 0) << 1;
        return res;
    }
    bool get_intersection(const circle& cir, point& c1, point& c2) const {
        double d = (c - cir.c).len();
        if (sgn(d - (r + cir.r)) >= 0 || sgn(d - abs(r - cir.r)) <= 0)
            return false;
        double p = (d + r + cir.r) / 2.0;
        double h = sqrt(abs(p * (p - d) * (p - r) * (p - cir.r))) * 2.0 / d;
        point pp = c + (cir.c - c).trunc((r * r + d * d - cir.r * cir.r) / (2.0 * d));
        c1 = pp - (cir.c - c).rotate_left().trunc(h);
        c2 = pp + (cir.c - c).rotate_left().trunc(h);
        return true;
    }
    bool get_tangency_points(const point& p, point& t1, point& t2) const {
        double d = (p - c).len();
        if (sgn(d - r) <= 0)
            return false;
        point pp = c + (p - c).trunc(r * r / d);
        double h = sqrt(abs(r * r - (r * r * r * r) / (d * d)));
        t1 = pp - (p - c).rotate_left().trunc(h);
        t2 = pp + (p - c).rotate_left().trunc(h);
        return true;
    }
    vector<pair<point, point> > get_tangency_points(const circle& cir) const {
        vector<pair<point, point> > t;
        double d = (c - cir.c).len();
        if (sgn(d - abs(cir.r - r)) <= 0)
            return t;
        double l = sqrt(abs(d * d - (cir.r - r) * (cir.r - r)));
        double h1 = r * l / d, h2 = cir.r * l / d;
        point p = (r > cir.r ? cir.c - c : c - cir.c);
        point pp1 = c + p.trunc(sqrt(abs(r * r - h1 * h1))), pp2 = cir.c + p.trunc(sqrt(abs(cir.r * cir.r - h2 * h2)));
        t.push_back(make_pair(pp1 + p.rotate_left().trunc(h1), pp2 + p.rotate_left().trunc(h2)));
        t.push_back(make_pair(pp1 - p.rotate_left().trunc(h1), pp2 - p.rotate_left().trunc(h2)));
        if (sgn(d - (r + cir.r)) <= 0)
            return t;
        double d1 = d * r / (r + cir.r), d2 = d * cir.r / (r + cir.r);
        point pp3 = c + (cir.c - c).trunc(r * r / d1), pp4 = cir.c + (c - cir.c).trunc(cir.r * cir.r / d2);
        double h3 = sqrt(abs(r * r - (r * r * r * r) / (d1 * d1))), h4 = sqrt(abs(cir.r * cir.r - (cir.r * cir.r * cir.r * cir.r) / (d2 * d2)));
        t.push_back(make_pair(pp3 + (cir.c - c).rotate_left().trunc(h3), pp4 + (c - cir.c).rotate_left().trunc(h4)));
        t.push_back(make_pair(pp3 - (cir.c - c).rotate_left().trunc(h3), pp4 - (c - cir.c).rotate_left().trunc(h4)));
        return t;
    }
    double get_intersection_area(const point& p1, const point& p2) const {
        point v1 = (p1 - c), v2 = (p2 - c);
        double d1 = v1.len(), d2 = v2.len();
        point c1, c2;
        int s = get_intersection(p1, p2, c1, c2);
        if (s == 0) {
            if (sgn(d1 - r) > 0 && sgn(d2 - r) > 0) {
                double t = trim((v1 ^ v2) / (d1 * d2));
                return r * r * acos(t) / 2.0;
            }
            return abs(v1 * v2 / 2.0);
        }
        if (s == 1) {
            point k = c1 - c;
            double t = trim((v1 ^ k) / (d1 * k.len()));
            return abs(v2 * k / 2.0) + r * r * acos(t) / 2.0;
        }
        if (s == 2) {
            point k = c2 - c;
            double t = trim((v2 ^ k) / (d2 * k.len()));
            return abs(v1 * k / 2.0) + r * r * acos(t) / 2.0;
        }
        point k1 = c1 - c, k2 = c2 - c;
        double t1 = trim((v1 ^ k1) / (d1 * k1.len()));
        double t2 = trim((v2 ^ k2) / (d2 * k2.len()));
        return abs(k1 * k2 / 2.0) + r * r * (acos(t1) + acos(t2)) / 2.0;
    }
    double get_intersection_area(const circle& cir) const {
        double d = (c - cir.c).len();
        if (sgn(d - (r + cir.r)) >= 0)
            return 0;
        if (sgn(d - abs(r - cir.r)) <= 0)
            return min(area(), cir.area());
        double c1 = trim((r * r + d * d - cir.r * cir.r) / (2.0 * r * d));
        double c2 = trim((cir.r * cir.r + d * d - r * r) / (2.0 * cir.r * d));
        double p = (r + cir.r + d) / 2.0;
        double s = sqrt(p * (p - r) * (p - cir.r) * (p - d));
        return acos(c1) * r * r + acos(c2) * cir.r * cir.r - s * 2.0;
    }
};
