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
