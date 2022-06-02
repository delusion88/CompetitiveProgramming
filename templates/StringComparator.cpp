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
const long long modA = 998244353, modB = 1000000007;

struct StringComparator {
    struct HashInt {
        long long a, b;
        HashInt (): a(0), b(0) { }
        HashInt (long long x): a(x), b(x) { }
        HashInt (long long a, long long b): a(a), b(b) { }
        friend HashInt operator+ (const HashInt lhs, const HashInt rhs) {
            return HashInt ((lhs.a + rhs.a) % modA, (lhs.b + rhs.b) % modB);
        }
        friend HashInt operator- (const HashInt lhs, const HashInt rhs) {
            return HashInt ((lhs.a - rhs.a + modA) % modA, (lhs.b - rhs.b + modB) % modB);
        }
        friend HashInt operator* (const HashInt lhs, const long long x) {
            return HashInt ((lhs.a * x) % modA, (lhs.b * x) % modB);
        }
        friend HashInt operator* (const HashInt lhs, const HashInt rhs) {
            return HashInt ((lhs.a * rhs.a) % modA, (lhs.b * rhs.b) % modB);
        }
        friend bool operator== (const HashInt lhs, const HashInt rhs) {
            return lhs.a == rhs.a && lhs.b == rhs.b;
        }
        explicit operator long long () const {
            return a * modB + b + 1;
        }
    };
    long long p = 239;
    string s;
    vector<HashInt> h, pows;
    StringComparator (string s): s(s) {
        h.assign(s.size() + 1, 0);
        for (int i = 0; i < s.size(); ++i)
            h[i + 1] = h[i] * p + s[i];
        pows.emplace_back(HashInt(1));
        for (int i = 0; i <= s.size(); ++i)
            pows.push_back(pows.back() * p);
    }
    HashInt substr (int idx, int len) const {
        return h[idx + len] - h[idx] * pows[len];
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
