const double eps = 1e-8;
const double pi = acos(-1.0);

int sgn(double d) {
    return d > eps ? 1 : (d < -eps ? -1 : 0);
}

double trim(double d, double l = 1.0) {
    return d > l ? l : (d < -l ? -l : d);
}
