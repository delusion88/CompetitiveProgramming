struct DSU {
    size_t size;
    vector<int> p;
    DSU() { }
    DSU(size_t size): size(size) {
        p.resize(size);
        iota(p.begin(), p.end(), 0);
    }
    int get(int v) {
        return(v == p[v]) ? v : p[v] = get(p[v]);
    }
    void unite(int u, int v) {
        u = get(u);
        v = get(v);
        if(u == v)
            return;
        p[v] = u;
    }
};
