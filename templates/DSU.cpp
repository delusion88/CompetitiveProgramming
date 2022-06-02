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
