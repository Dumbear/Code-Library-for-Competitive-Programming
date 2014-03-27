struct point {
    double x, y, z;
    point(double _x = 0, double _y = 0, double _z = 0): x(_x), y(_y), z(_z) {
    }
    void input() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    double len() const {
        return sqrt(x * x + y * y + z * z);
    }
    point trunc(double l) const {
        double r = l / len();
        return point(x * r, y * r, z * r);
    }
    point rotate(point axis, double ang) {
        axis = axis.trunc(1.0);
        double x = axis.x, y = axis.y, z = axis.z, c = cos(ang), s = sin(ang);
        double r[3][3] = {
            {x * x + (1.0 - x * x) * c, x * y * (1.0 - c) - z * s, x * z * (1.0 - c) + y * s},
            {y * x * (1.0 - c) + z * s, y * y + (1.0 - y * y) * c, y * z * (1.0 - c) - x * s},
            {z * x * (1.0 - c) - y * s, z * y * (1.0 - c) + x * s, z * z + (1.0 - z * z) * c}
        };
        double rx = r[0][0] * this->x + r[0][1] * this->y + r[0][2] * this->z;
        double ry = r[1][0] * this->x + r[1][1] * this->y + r[1][2] * this->z;
        double rz = r[2][0] * this->x + r[2][1] * this->y + r[2][2] * this->z;
        return point(rx, ry, rz);
    }
};

bool operator==(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0 && sgn(p1.z - p2.z) == 0;
}

bool operator!=(const point& p1, const point& p2) {
    return !(p1 == p2);
}

bool operator<(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? (sgn(p1.y - p2.y) == 0 ? sgn(p1.z - p2.z) < 0 : p1.y < p2.y) : p1.x < p2.x;
}

bool operator>(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? (sgn(p1.y - p2.y) == 0 ? sgn(p1.z - p2.z) > 0 : p1.y > p2.y) : p1.x > p2.x;
}

point operator+(const point& p1, const point& p2) {
    return point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

point operator-(const point& p1, const point& p2) {
    return point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

double operator^(const point& p1, const point& p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

point operator*(const point& p1, const point& p2) {
    return point(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);
}

point operator*(const point& p, double r) {
    return point(p.x * r, p.y * r, p.z * r);
}

point operator/(const point& p, double r) {
    return point(p.x / r, p.y / r, p.z / r);
}
