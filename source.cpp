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

const int Inf       = 0x4f4f4f4f;
const long long inf = 1100000000000000000;

void solve_case () {
    
}
 
signed main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    long long Tc = 1;
    cin >> Tc;
    for (long long testCase = 1; testCase <= Tc; ++testCase, cout << '\n') {
        solve_case();
    }
}
