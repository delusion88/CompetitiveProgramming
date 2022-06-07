struct MaxMerger {
    void operator()(int& res, int& a, int& b) const {
        res = max(a, b);
    }
};

template <
    typename T,
    typename Merge = MaxMerger
>
struct LazySegmentTree {
    int n;
    T neutral;
    Merge merge;
    vector<T> tr, lz;
    vector<bool>  clz;
    LazySegmentTree (int n, T neutral): n(n), neutral(neutral) {
        tr.assign (4 * n + 5, neutral);
        lz.assign (4 * n + 5, 0);
        clz.assign (4 * n + 5, 0);
        merge = Merge();
    }
    void push (int node, int l, int r) {
        if (!clz[node])
            return;
        if (l != r) {
            clz[node * 2 + 1] = 1;
            clz[node * 2 + 2] = 1;
            lz[node * 2 + 1] = lz[node];
            lz[node * 2 + 2] = lz[node];
        }
        tr[node] = lz[node] * (r - l + 1);
        lz[node] = 0;
        clz[node] = 0;
    }
    T _get (int node, int l, int r, int ql, int qr) {
        push (node, l, r);
        if (l >= ql && r <= qr) {
            return tr[node];
        }
        if (l > qr || r < ql) {
            return neutral;
        }
        int m = (l + r) / 2;
        T a = _get (node * 2 + 1, l, m, ql, qr),
          b = _get (node * 2 + 2, m + 1, r, ql, qr),
          cur;
        merge (cur, a, b);
        return cur;
    }
    void _upd (int node, int l, int r, int ql, int qr, T val) {
        push (node, l, r);
        if (l >= ql && r <= qr) {
            clz[node] = 1;
            lz[node] = val;
            push (node, l, r);
            return;
        }
        if (l > qr || r < ql) {
            return;
        }
        int m = (l + r) / 2;
        _upd (node * 2 + 1, l, m, ql, qr, val);
        _upd (node * 2 + 2, m + 1, r, ql, qr, val);
        merge (tr[node], tr[node * 2 + 1], tr[node * 2 + 2]);
    }
    T get (int l, int r) {
        return _get (0, 0, n - 1, l, r);
    }
    void update (int l, int r, T val) {
        _upd (0, 0, n - 1, l, r, val);
    }
    void update (int idx, T val) {
        _upd (0, 0, n - 1, idx, idx, val);
    }
};

template <
    typename T,
    typename Merge = MaxMerger
>
struct SegmentTree {
    int n;
    T neutral;
    Merge merge;
    vector<T> tr;
    SegmentTree (int n, T neutral): n(n), neutral(neutral) {
        tr.assign (4 * n + 5, neutral);
        merge = Merge();
    }
    T _get (int node, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return tr[node];
        }
        if (l > qr || r < ql) {
            return neutral;
        }
        int m = (l + r) / 2;
        T a = _get (node * 2 + 1, l, m, ql, qr),
          b = _get (node * 2 + 2, m + 1, r, ql, qr),
          cur;
        merge (cur, a, b);
        return cur;
    }
    void _upd (int node, int l, int r, int ql, int qr, T val) {
        if (ql == l && qr == r) {
            tr[node] = val;
            return;
        }
        if (l > qr || r < ql) {
            return;
        }
        int m = (l + r) / 2;
        _upd (node * 2 + 1, l, m, ql, qr, val);
        _upd (node * 2 + 2, m + 1, r, ql, qr, val);
        merge (tr[node], tr[node * 2 + 1], tr[node * 2 + 2]);
    }
    T get (int l, int r) {
        return _get (0, 0, n - 1, l, r);
    }
    void update (int l, int r, T val) {
        _upd (0, 0, n - 1, l, r, val);
    }
    void update (int idx, T val) {
        _upd (0, 0, n - 1, idx, idx, val);
    }
};

