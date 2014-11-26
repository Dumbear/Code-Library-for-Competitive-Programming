struct link_cut_tree {
    struct node {
        node *parent;
        node *child_l;
        node *child_r;
        bool reversed;
        node(): parent(NULL), child_l(NULL), child_r(NULL), reversed(false) {
            /* All the maintained values should be initialized here */
        }
        inline bool is_root() {
            return parent == NULL || (this != parent->child_l && this != parent->child_r);
        }
        inline int child_side() {
            if (parent == NULL)
                return 0;
            else if (this == parent->child_l)
                return -1;
            else if (this == parent->child_r)
                return +1;
            return 0;
        }
        inline void push_down() {
            if (reversed) {
                if (child_l != NULL)
                    child_l->reversed ^= true;
                if (child_r != NULL)
                    child_r->reversed ^= true;
                swap(child_l, child_r);
                reversed = false;
            }
            /* Values of current node that need to cover the tree should be pushed down to the child nodes here */
        }
        void push_down_from_root() {
            if (!is_root())
                parent->push_down_from_root();
            push_down();
        }
        inline void update() {
            /* Maintained tree values of current node should be updated from the child nodes here */
        }
    };
    static void splay(node *v) {
        v->push_down_from_root();
        while (!v->is_root()) {
            node *p = v->parent, *pp = p->parent;
            if (p->is_root()) {
                v == p->child_l ? zig(v) : zag(v);
            } else if (p == pp->child_l && v == p->child_l) {
                zig(p);
                zig(v);
            } else if (p == pp->child_r && v == p->child_r) {
                zag(p);
                zag(v);
            } else if (p == pp->child_l && v == p->child_r) {
                zag(v);
                zig(v);
            } else if (p == pp->child_r && v == p->child_l) {
                zig(v);
                zag(v);
            }
        }
        v->update();
    }
    static void zig(node *v) {
        node *p = v->parent, *pp = p->parent;
        link_child(pp, v, p->child_side());
        link_child(p, v->child_r, -1);
        link_child(v, p, +1);
        p->update();
    }
    static void zag(node *v) {
        node *p = v->parent, *pp = p->parent;
        link_child(pp, v, p->child_side());
        link_child(p, v->child_l, +1);
        link_child(v, p, -1);
        p->update();
    }
    static void link_child(node *p, node *v, int side) {
        if (p != NULL && side != 0) {
            if (side == -1)
                p->child_l = v;
            else
                p->child_r = v;
        }
        if (v != NULL)
            v->parent = p;
    }
    static void access(node *v) {
        node *last = NULL;
        while (v != NULL) {
            splay(v);
            v->child_r = last;
            v->update();
            last = v;
            v = v->parent;
        }
    }
    static void rootify(node *v) {
        access(v);
        splay(v);
        v->reversed = true;
    }
    static node *find_root(node *v) {
        access(v);
        splay(v);
        while (v->child_l != NULL)
            v = v->child_l;
        splay(v);
        return v;
    }
    static void link(node *u, node *v) {
        rootify(u);
        u->parent = v;
        access(u);
    }
    /* Cut the edge of node v and it's parent, when node u is the root */
    static void cut(node *u, node *v) {
        rootify(u);
        access(v);
        splay(v);
        v->child_l->parent = NULL;
        v->child_l = NULL;
        v->update();
    }
    static void update_vertex(node *v) {
        rootify(v);
        /* Maintained node values of node v should be updated here */
        v->update();
    }
    static void query_vertex(node *v) {
        splay(v);
        /* Maintained node values of node v should be returned here */
    }
    static void update_path(node *u, node *v) {
        rootify(u);
        access(v);
        splay(v);
        /* Values that need to cover the tree should be set to node v here, it's the path from u to v */
    }
    static void query_path(node *u, node *v) {
        rootify(u);
        access(v);
        splay(v);
        /* Maintained tree values of node v should be returned here, it's the path from u to v */
    }
};
