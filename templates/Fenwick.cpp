template <
    typename T
>
struct Fenwick {
    vector <T> tr;
    Fenwick (size_t size) {
        tr.assign(size, 0);
    }
    void update (size_t idx, T delta) {
        for (; idx < tr.size(); idx |= idx + 1)
            tr[idx] += delta;
    }
    T get (long long r) {
        if (r < 0)
            return 0;
        T res = 0;
        for (++r; r > 0; r &= r - 1)
            res += tr[r - 1];
        return res;
    }
    T get (long long l, long long r) {
        return get (r) - get(l - 1);
    }
};

template <
    typename T
>
struct Gigachad {
    vector <T> tr;
    Gigachad () { }
    Gigachad (size_t size) {
        tr.assign(size + 2, 0);
    }
    void update (int idx, T delta) {
        for (++idx; idx < tr.size(); idx += idx & -idx)
            tr[idx] += delta;
    }
    void update (int l, int r, T delta) {
        update(l, delta);
        update(r + 1, -delta);
    }
    T get (long long r) {
        if (r <= 0)
            return 0;
        T res = 0;
        for (++r; r > 0; r -= r & -r)
            res += tr[r];
        return res;
    }
};

template <
    typename T
>
struct HyperGigaChad {
    Gigachad<T> G1, G2;
    HyperGigaChad (size_t size) {
        G1 = Gigachad<T>(size);
        G2 = Gigachad<T>(size);
    }
    void update (int l, int r, int delta) {
        G1.update(l, r, delta);
        G2.update(l, delta * (l - 1));
        G2.update(r + 1, -delta * r);
    }
    T get (int r) {
        return G1.get(r) * r - G2.get(r);
    }
    T get (int l, int r) {
        return get(r) - get(l - 1);
    }
};