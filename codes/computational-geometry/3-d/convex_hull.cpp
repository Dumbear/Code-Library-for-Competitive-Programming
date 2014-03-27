struct face {
    int a, b, c;
    face(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c) {
    }
};

const int max_n = 0xff, max_f = max_n * 2;

int n1, n2, pos[max_n][max_n];
face buf1[max_f], buf2[max_f], *p1, *p2;

int get_position(const point& p, const point& p1, const point& p2, const point& p3) {
    return sgn((p2 - p1) * (p3 - p1) ^ (p - p1));
}

void check(int k, int a, int b, int s) {
    if (pos[b][a] == 0) {
        pos[a][b] = s;
        return;
    }
    if (pos[b][a] != s)
        p2[n2++] = (s < 0 ? face(k, b, a) : face(k, a, b));
    pos[b][a] = 0;
}

void get_convex_hull(point* p, int n, face* pol, int& m) {
    for (int i = 1; i < n; ++i) {
        if (p[i] != p[0]) {
            swap(p[i], p[1]);
            break;
        }
    }
    for (int i = 2; i < n; ++i) {
        if (sgn(((p[0] - p[i]) * (p[1] - p[i])).len()) != 0) {
            swap(p[i], p[2]);
            break;
        }
    }
    for (int i = 3; i < n; ++i) {
        if (get_position(p[i], p[0], p[1], p[2]) != 0) {
            swap(p[i], p[3]);
            break;
        }
    }
    p1 = buf1;
    p2 = buf2;
    n1 = n2 = 0;
    memset(pos, 0, sizeof(pos));
    p1[n1++] = face(0, 1, 2);
    p1[n1++] = face(2, 1, 0);
    for (int i = 3; i < n; ++i) {
        n2 = 0;
        for (int j = 0; j < n1; ++j) {
            int s = get_position(p[i], p[p1[j].a], p[p1[j].b], p[p1[j].c]);
            if (s == 0)
                s = -1;
            if (s <= 0)
                p2[n2++] = p1[j];
            check(i, p1[j].a, p1[j].b, s);
            check(i, p1[j].b, p1[j].c, s);
            check(i, p1[j].c, p1[j].a, s);
        }
        swap(p1, p2);
        swap(n1, n2);
    }
    m = n1;
    copy(p1, p1 + n1, pol);
}
