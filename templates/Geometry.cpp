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
const long double eps = 0.000000001;
const long double pi = acos (-1);

struct Vector {
    long double x, y;
    Vector ( ): x(0), y(0) { }
    Vector (long double x, long double y): x(x), y(y) { }
    friend Vector operator+ (const Vector lhs, const Vector rhs) {
        return Vector (lhs.x + rhs.x, lhs.y + rhs.y);
    }
    Vector operator+= (const Vector rhs) {
        return *this = *this + rhs;
    }
    friend Vector operator- (const Vector lhs, const Vector rhs) {
        return Vector (lhs.x - rhs.x, lhs.y - rhs.y);
    }
    Vector operator-= (const Vector rhs) {
        return *this = *this - rhs;
    }
    friend Vector operator* (const Vector lhs, const long double rhs) {
        return Vector (lhs.x * rhs, lhs.y * rhs);
    }
    Vector operator*= (const long double rhs) {
        return *this = *this * rhs;
    }
    friend Vector operator/ (const Vector lhs, const long double rhs) {
        return Vector (lhs.x / rhs, lhs.y / rhs);
    }
    Vector operator/= (const long double rhs) {
        return *this = *this / rhs;
    }
    friend long double operator* (const Vector lhs, const Vector rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    friend long double operator% (const Vector lhs, const Vector rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
    long double angle () const {
        return (atan2 (y, x) < 0 ? atan2 (y, x) + pi * 2 : atan2 (y, x));
    }
    long double length () const {
        return hypotl (x, y);
    }
    friend Vector operator/ (const Vector lhs, const Vector rhs) {
        return Vector (lhs.x / rhs.x, lhs.y / rhs.y);
    }
    Vector operator/= (const Vector rhs) {
        return *this = *this / rhs;
    }
    friend bool operator== (const Vector lhs, const Vector rhs) {
        return abs(lhs.x - rhs.x) <= eps && abs(lhs.y - rhs.y) <= eps;
    }
    friend bool operator!= (const Vector lhs, const Vector rhs) {
        return !(lhs == rhs);
    }
    friend ostream& operator<< (ostream& out, const Vector rhs) {
        out << rhs.x << ' ' << rhs.y;
        return out;
    }
    friend istream& operator>> (istream& in, Vector &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }
};

struct Polygon {
    vector <Vector> p;
    Polygon ( ) { }
    Polygon (vector<Vector> p): p(p) { }
    size_t size () const {
        return p.size();
    }
    Vector& operator[] (size_t x) {
        return p[x];
    }
    Vector back () const {
        return p.back ();
    }
    void pop_back () {
        p.pop_back ();
    }
    void push_back (Vector v) {
        p.push_back (v);
    }
    long double area () {
        long double res = 0;
        size_t sz = size();
        for (size_t i = 0; i < sz; ++i) {
            Vector& x = p[i];
            Vector& y = (i ? p[i - 1] : p.back());
            res += (x.x - y.x) * (x.y + y.y);
        }
        return abs(res) / 2;
    }
};

long double angle (Vector a, Vector b) {
    return abs(atan2 (a % b, a * b));
}

Polygon ConvexHull (vector<Vector> p) {
    Vector s = p[0];
    for (auto v : p) {
        if (v.y < s.y || (v.y == s.y && v.x < s.x))
            s = v;
    }
    sort (p.begin (), p.end (), [&] (Vector a, Vector b) {
        return ((Vector (a) - s) % (Vector (b) - s)) > 0;
    });
    Polygon hull;
    for (auto v : p) {
        while (hull.size () >= 2) {
            Vector vec = v - hull.back ();
            Vector vec1 = hull.back () - hull[hull.size () - 2];
            if (vec % vec1 > 0)
                hull.pop_back ();
            else
                break;
        }
        hull.push_back (v);
    }
    return hull;
}

void solve () {
    
}

signed main () {
    cout.precision(14);
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    long long Tc = 1;
    // cin >> Tc;
    for (long long testCase = 1; testCase <= Tc; ++testCase, cout << '\n') {
        solve();
    }
}
