struct event {
    point p;
    double ang;
    int d;
    event() {
    }
    event(const point& _p, const point& c, int _d): p(_p), d(_d) {
        ang = atan2(p.y - c.y, p.x - c.x);
        if (sgn(ang - pi) == 0)
            ang = -pi;
    }
};

bool operator<(const event& e1, const event& e2) {
    return e1.ang < e2.ang;
}

int n, n_e;
circle cir[max_n];
event e[max_n * 2];
double areas[max_n];

double get_area(const point& c, double r, const point& p1, const point& p2) {
    point v1 = p1 - c, v2 = p2 - c;
    double ang = acos(trim((v1 ^ v2) / (r * r)));
    double area1 = ang * r * r / 2.0 - abs(v1 * v2) / 2.0, area2 = p1 * p2 / 2.0;
    if (sgn(v1 * v2) < 0) {
        ang = 2.0 * pi - ang;
        area1 = pi * r * r - area1;
    }
    return area1 + area2;
}

void compute_areas(int id) {
    n_e = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (i == id)
            continue;
        if (cir[i].contains(cir[id]))
            ++cnt;
        point c1, c2;
        if (!cir[id].get_intersection(cir[i], c1, c2))
            continue;
        e[n_e++] = event(c1, cir[id].c, 1);
        e[n_e++] = event(c2, cir[id].c, -1);
        if (e[n_e - 1] < e[n_e - 2])
            ++cnt;
    }
    if (n_e == 0) {
        areas[cnt] += cir[id].area();
        return;
    }
    sort(e, e + n_e);
    e[n_e] = e[0];
    for (int i = 0; i < n_e; ++i) {
        cnt += e[i].d;
        if (sgn(e[i].ang - e[i + 1].ang) != 0)
            areas[cnt] += get_area(cir[id].c, cir[id].r, e[i].p, e[i + 1].p);
    }
}

void compute_areas() {
    fill(areas, areas + n, 0.0);
    for (int i = 0; i < n; ++i)
        compute_areas(i);
    for (int i = 0; i < n - 1; ++i)
        areas[i] -= areas[i + 1];
}
