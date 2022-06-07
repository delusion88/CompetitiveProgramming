struct SPMaxMerger {
    int operator()(int a, int b) const {
        return max(a, b);
    }
};

template <
    typename T,
    typename SPMerge = SPMaxMerger
>
struct SparseTable {
    size_t size, k;
    vector<vector<T>> sparse;
    SPMerge merge;
    SparseTable (): merge (SPMerge()) { }
    SparseTable (size_t size): merge (SPMerge()), size (size), k (__lg (size) + 1) {
        sparse.assign (k, vector<T> (size));
    } 
    SparseTable (vector<T> v): merge (SPMerge()), size (v.size()), k (__lg (size) + 1) {
        sparse.assign (k, vector<T> (size, 0));  
        sparse[0] = v;  
        for (int l = 1; l < k; ++l)
            for (int i = 0; i + (1 << l) <= size; ++i)
                sparse[l][i] = merge (sparse[l - 1][i], sparse[l - 1][i + (1 << (l - 1))]);
    }
    T get (int l, int r) {
        int lg = __lg (r - l + 1);
        return merge (sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
    }
};
