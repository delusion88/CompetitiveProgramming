#include <bits/stdc++.h>

using namespace std;

const long long inf = 1100000000000000000;
const int Inf = 0x4f4f4f4f;

struct Fenwick {
    vector <long long> tr;
    Fenwick (size_t size) {
        tr.assign(size, 0);
    }
    void update (size_t idx, long long delta) {
        for (; idx < tr.size(); idx |= idx + 1)
            tr[idx] += delta;
    }
    long long get (long long r) {
        if (r < 0)
            return 0;
        long long res = 0;
        for (++r; r > 0; r &= r - 1)
            res += tr[r - 1];
        return res;
    }
    long long get (long long l, long long r) {
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
