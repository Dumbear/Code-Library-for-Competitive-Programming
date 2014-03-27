struct half_plane {
    point p1, p2;
    double ang;
    half_plane() {
    }
    half_plane(const point& _p1, const point& _p2): p1(_p1), p2(_p2) {
        ang = atan2(p2.y - p1.y, p2.x - p1.x);
        if (sgn(ang - pi) == 0)
            ang = -pi;
    }
    int get_position(const point& p) const {
        return sgn((p2 - p1) * (p - p1));
    }
};

bool operator<(const half_plane& pl1, const half_plane& pl2) {
    return sgn(pl1.ang - pl2.ang) == 0 ? pl1.get_position(pl2.p1) < 0 : pl1.ang < pl2.ang;
}

double operator^(const half_plane& pl1, const half_plane& pl2) {
    return (pl1.p2 - pl1.p1) ^ (pl2.p2 - pl2.p1);
}

double operator*(const half_plane& pl1, const half_plane& pl2) {
    return (pl1.p2 - pl1.p1) * (pl2.p2 - pl2.p1);
}

point get_intersection(const half_plane& pl1, const half_plane& pl2) {
    double d1 = (pl1.p2 - pl1.p1) * (pl2.p1 - pl1.p1), d2 = (pl1.p2 - pl1.p1) * (pl2.p2 - pl1.p1);
    return (pl2.p1 * d2 - pl2.p2 * d1) / (d2 - d1);
}

void get_intersection(const half_plane* pl, int n, point* pol, int& m) {
    m = 0;
    deque<int> deq1;
    deque<point> deq2;
    deq1.push_back(0);
    deq1.push_back(1);
    deq2.push_back(get_intersection(pl[0], pl[1]));
    for (int i = 2; i < n; ++i) {
        while (!deq2.empty() && pl[i].get_position(deq2.back()) <= 0) {
            if (sgn(pl[deq1[deq1.size() - 2]] * pl[i]) <= 0 && sgn(pl[deq1.back()] * pl[i]) >= 0)
                return;
            deq1.pop_back();
            deq2.pop_back();
        }
        while (!deq2.empty() && pl[i].get_position(deq2.front()) <= 0) {
            deq1.pop_front();
            deq2.pop_front();
        }
        deq2.push_back(get_intersection(pl[deq1.back()], pl[i]));
        deq1.push_back(i);
        while (deq2.size() > 1 && pl[deq1.front()].get_position(deq2.back()) <= 0) {
            deq1.pop_back();
            deq2.pop_back();
        }
        while (deq2.size() > 1 && pl[deq1.back()].get_position(deq2.front()) <= 0) {
            deq1.pop_front();
            deq2.pop_front();
        }
    }
    m = deq2.size();
    copy(deq2.begin(), deq2.end(), pol);
    pol[m++] = get_intersection(pl[deq1.front()], pl[deq1.back()]);
}
