#include <bits/stdc++.h>

using namespace std;

const long long inf = 1100000000000000000;
const int Inf = 0x4f4f4f4f;

template <
    typename T
>
struct SparseTable {
    size_t size, k;
    vector<vector<T>> sparse;
    T merge (T a, T b) {
        return max (a, b);
    }
    SparseTable () { }
    SparseTable (size_t size): size (size), k (__lg (size) + 1) {
        sparse.assign (k, vector<T> (size));
    } 
    SparseTable (vector<T> v): size (v.size()), k (__lg (size) + 1) {
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

void solve () {
    
}
 
signed main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    long long Tc = 1;
    // cin >> Tc;
    for (long long testCase = 1; testCase <= Tc; ++testCase, cout << '\n') {
        solve();
    }
}
