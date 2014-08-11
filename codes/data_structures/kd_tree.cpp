struct kd_tree {
    struct node {
        int l, r, x1, y1, x2, y2, cnt, delta, sum;
        node(int _x1, int _y1, int _x2, int _y2, int _cnt): l(-1), r(-1), x1(_x1), y1(_y1), x2(_x2), y2(_y2), cnt(_cnt), delta(0), sum(0) {
        }
    };
    struct less_equal_x : binary_function<point, point, bool> {
        bool operator()(const point& p1, const point& p2) const {
            return p1.x <= p2.x;
        }
    };
    struct less_equal_y : binary_function<point, point, bool> {
        bool operator()(const point& p1, const point& p2) const {
            return p1.y <= p2.y;
        }
    };
    vector<node> nodes;
    void clear() {
        nodes.clear();
    }
    void build(point* p, int from, int to, int id = 0) {
        int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;
        for (int i = from; i < to; ++i) {
            if (p[i].x < min_x)
                min_x = p[i].x;
            if (p[i].x > max_x)
                max_x = p[i].x;
            if (p[i].y < min_y)
                min_y = p[i].y;
            if (p[i].y > max_y)
                max_y = p[i].y;
        }
        nodes.push_back(node(min_x, min_y, max_x, max_y, to - from));
        int dx = max_x - min_x, dy = max_y - min_y, mid = -1;
        if (dx == 0 && dy == 0)
            return;
        if (dx > dy) {
            int k = (min_x + max_x) / 2;
            mid = partition(p + from, p + to, bind2nd(less_equal_x(), point(k, 0))) - p;
        } else {
            int k = (min_y + max_y) / 2;
            mid = partition(p + from, p + to, bind2nd(less_equal_y(), point(0, k))) - p;
        }
        if (from < mid) {
            nodes[id].l = nodes.size();
            build(p, from, mid, nodes.size());
        }
        if (mid < to) {
            nodes[id].r = nodes.size();
            build(p, mid, to, nodes.size());
        }
    }
    int add(int x1, int y1, int x2, int y2, int delta, int id = 0) {
        node &v = nodes[id];
        if (x1 > v.x2 || x2 < v.x1 || y1 > v.y2 || y2 < v.y1)
            return 0;
        if (x1 <= v.x1 && x2 >= v.x2 && y1 <= v.y1 && y2 >= v.y2) {
            v.delta += delta;
            return v.cnt;
        }
        int res = 0;
        if (v.l != -1)
            res += add(x1, y1, x2, y2, delta, v.l);
        if (v.r != -1)
            res += add(x1, y1, x2, y2, delta, v.r);
        v.sum += res * delta;
        return res;
    }
    int get_sum(int x1, int y1, int x2, int y2, int id = 0) {
        node &v = nodes[id];
        if (x1 > v.x2 || x2 < v.x1 || y1 > v.y2 || y2 < v.y1)
            return 0;
        push_down(id);
        if (x1 <= v.x1 && x2 >= v.x2 && y1 <= v.y1 && y2 >= v.y2)
            return v.sum;
        int res = 0;
        if (v.l != -1)
            res += get_sum(x1, y1, x2, y2, v.l);
        if (v.r != -1)
            res += get_sum(x1, y1, x2, y2, v.r);
        return res;
    }
    void push_down(int id) {
        node &v = nodes[id];
        v.sum += v.cnt * v.delta;
        if (v.l != -1)
            nodes[v.l].delta += v.delta;
        if (v.r != -1)
            nodes[v.r].delta += v.delta;
        v.delta = 0;
    }
};
