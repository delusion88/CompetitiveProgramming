#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using ordered_set = 
      __gnu_pbds::tree <
          long long,
          __gnu_pbds::null_type,
          less <
          long long >,
          __gnu_pbds::rb_tree_tag,
          __gnu_pbds::tree_order_statistics_node_update >;

std::mt19937_64 rnd64 (
    std::chrono::high_resolution_clock::now ().time_since_epoch ().count () );

const long long inf = 1100000000000000000;
const int Inf = 0x4f4f4f4f;

template <
    typename T
>
struct SegmentTree {
    int n;
    T neutral;
    vector<T> tr, lz;
    vector<bool>  clz;
    SegmentTree (int n, T neutral): n(n), neutral(neutral) {
        tr.assign (4 * n + 5, neutral);
        lz.assign (4 * n + 5, 0);
        clz.assign (4 * n + 5, 0);
    }
    void merge (T& res, T& a, T& b) {
        res = a + b;
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
