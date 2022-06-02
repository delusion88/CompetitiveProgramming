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

const long long inf = 1100000000000000000, mod = 1000000007;
const int Inf = 0x4f4f4f4f;

struct Modular {
    long long val;
    
    Modular (long long x) {
        if (x < 0) {
            x %= mod;
            x += mod;
        }
        if (x >= mod) {
            x %= mod;
        }
        val = x;
    }
    Modular (): val(0) { }

    friend Modular operator+ (const Modular lhs, const Modular rhs) {
        return (lhs.val + rhs.val >= mod) ? lhs.val + rhs.val - mod : lhs.val + rhs.val;
    }

    Modular& operator+= (const Modular rhs) {
        return *this = *this + rhs;
    }
    friend Modular operator- (const Modular lhs, const Modular rhs) {
        return (lhs.val - rhs.val < 0) ? lhs.val - rhs.val + mod : lhs.val - rhs.val;
    }

    Modular& operator-= (const Modular rhs) {
        return *this = *this - rhs;
    }
    friend Modular operator- (const Modular rhs) {
        return mod - rhs;
    }

    friend Modular operator* (const Modular lhs, const Modular rhs) {
        return (lhs.val * rhs.val) % mod;
    }
    Modular& operator*= (const Modular rhs) {
        return *this = *this * rhs;
    }

    friend bool operator== (const Modular lhs, const Modular rhs) {
        return lhs.val == rhs.val;
    }
    friend bool operator!= (const Modular lhs, const Modular rhs) {
        return lhs.val != rhs.val;
    }
    friend bool operator< (const Modular lhs, const Modular rhs) {
        return lhs.val < rhs.val;
    }
    friend bool operator<= (const Modular lhs, const Modular rhs) {
        return lhs.val <= rhs.val;
    }
    friend bool operator> (const Modular lhs, const Modular rhs) {
        return lhs.val > rhs.val;
    }
    friend bool operator>= (const Modular lhs, const Modular rhs) {
        return lhs.val >= rhs.val;
    }

    friend Modular operator^ (Modular lhs, Modular rhs) {
        Modular res = 1;
        while (rhs != 0) {
            if (rhs.val & 1)
                res *= lhs;
            lhs *= lhs;
            rhs.val >>= 1;
        }
        return res;
    }
    Modular& operator^= (const Modular rhs) {
        return *this = (*this ^ rhs);
    }

    friend Modular operator* (const Modular rhs) {
        return rhs ^ (mod - 2);
    }

    friend Modular operator/ (const Modular lhs, const Modular rhs) {
        return lhs * (*rhs);
    }
    Modular& operator/= (const Modular rhs) {
        return *this = *this / rhs;
    }

    friend ostream& operator<< (ostream& out, const Modular rhs) {
        out << rhs.val;
        return out;
    }
    friend istream& operator>> (istream& in, Modular &rhs) {
        in >> rhs.val;
        if (rhs.val < 0) {
            rhs.val %= mod;
            rhs.val += mod;
        }
        if (rhs.val >= mod) {
            rhs.val %= mod;
        }
        return in;
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
