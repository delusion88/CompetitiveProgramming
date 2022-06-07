struct DSU {
    size_t size;
    vector<int> p, sz;
    DSU () { }
    DSU (size_t size): size(size) {
        p.resize (size);
        sz.assign (size, 1);
        iota (p.begin(), p.end(), 0);
    }
    int get (int v) {
        return (v == p[v]) ? v : p[v] = get(p[v]);
    }
    void unite (int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v)
            return;
        if (sz[v] > sz[u])
            swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
    }
};
