struct point {
    double x, y;
    point(double _x = 0, double _y = 0): x(_x), y(_y) {
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    point trunc(double l) const {
        double r = l / len();
        return point(x * r, y * r);
    }
    point rotate_left() const {
        return point(-y, x);
    }
    point rotate_left(double ang) const {
        double c = cos(ang), s = sin(ang);
        return point(x * c - y * s, y * c + x * s);
    }
    point rotate_right() const {
        return point(y, -x);
    }
    point rotate_right(double ang) const {
        double c = cos(ang), s = sin(ang);
        return point(x * c + y * s, y * c - x * s);
    }
};

bool operator==(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;
}

bool operator!=(const point& p1, const point& p2) {
    return !(p1 == p2);
}

bool operator<(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) < 0 : p1.x < p2.x;
}

bool operator>(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) > 0 : p1.x > p2.x;
}

point operator+(const point& p1, const point& p2) {
    return point(p1.x + p2.x, p1.y + p2.y);
}

point operator-(const point& p1, const point& p2) {
    return point(p1.x - p2.x, p1.y - p2.y);
}

double operator^(const point& p1, const point& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double operator*(const point& p1, const point& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

point operator*(const point& p, double r) {
    return point(p.x * r, p.y * r);
}

point operator/(const point& p, double r) {
    return point(p.x / r, p.y / r);
}
