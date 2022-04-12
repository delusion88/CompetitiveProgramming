#include <bits/stdc++.h>

using namespace std;

const long long inf = 1100000000000000000, mod = 1000000007;
const int Inf = 0x4f4f4f4f;
const long double eps = 0.000000001;
const long double pi = acos (-1);

struct Point {
    long double x, y;
    Point ( ): x(0), y(0) { }
    Point (long double x, long double y): x(x), y(y) { }
    friend Point operator+ (const Point lhs, const Point rhs) {
        return Point (lhs.x + rhs.x, lhs.y + rhs.y);
    }
    Point operator+= (const Point rhs) {
        return *this = *this + rhs;
    }
    friend Point operator- (const Point lhs, const Point rhs) {
        return Point (lhs.x - rhs.x, lhs.y - rhs.y);
    }
    Point operator-= (const Point rhs) {
        return *this = *this - rhs;
    }
    friend Point operator* (const Point lhs, const long double rhs) {
        return Point (lhs.x * rhs, lhs.y * rhs);
    }
    Point operator*= (const long double rhs) {
        return *this = *this * rhs;
    }
    friend Point operator/ (const Point lhs, const long double rhs) {
        return Point (lhs.x / rhs, lhs.y / rhs);
    }
    Point operator/= (const long double rhs) {
        return *this = *this / rhs;
    }
    friend bool operator== (const Point lhs, const Point rhs) {
        return abs(lhs.x - rhs.x) <= eps && abs(lhs.y - rhs.y) <= eps;
    }
    friend bool operator!= (const Point lhs, const Point rhs) {
        return !(lhs == rhs);
    }
    friend ostream& operator<< (ostream& out, const Point rhs) {
        out << rhs.x << ' ' << rhs.y;
        return out;
    }
    friend istream& operator>> (istream& in, Point &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }
};
struct Vector {
    Point a;
    Vector ( ) { }
    Vector (Point a): a(a) { }
    Vector (long double x, long double y): a(Point(x, y)) { }
    friend Vector operator+ (const Vector lhs, const Vector rhs) {
        return Vector (lhs.a + rhs.a);
    }
    Vector operator+= (const Vector rhs) {
        return *this = *this + rhs;
    }
    friend Vector operator- (const Vector lhs, const Vector rhs) {
        return Vector (lhs.a - rhs.a);
    }
    Vector operator-= (const Vector rhs) {
        return *this = *this - rhs;
    }
    friend Vector operator* (const Vector lhs, const long double rhs) {
        return Vector (lhs.a * rhs);
    }
    Vector operator*= (const long double rhs) {
        return *this = *this * rhs;
    }
    friend Vector operator/ (const Vector lhs, const long double rhs) {
        return Vector (lhs.a / rhs);
    }
    Vector operator/= (const long double rhs) {
        return *this = *this / rhs;
    }
    friend long double operator* (const Vector lhs, const Vector rhs) {
        return lhs.a.x * rhs.a.x + lhs.a.y * rhs.a.y;
    }
    friend long double operator% (const Vector lhs, const Vector rhs) {
        return lhs.a.x * rhs.a.y - lhs.a.y * rhs.a.x;
    }
    friend Vector operator/ (const Vector lhs, const Vector rhs) {
        return Vector (lhs.a.x / rhs.a.x, lhs.a.y / rhs.a.y);
    }
    Vector operator/= (const Vector rhs) {
        return *this = *this / rhs;
    }
    friend bool operator== (const Vector lhs, const Vector rhs) {
        return lhs.a == rhs.a;
    }
    friend bool operator!= (const Vector lhs, const Vector rhs) {
        return lhs.a != rhs.a;
    }
    long double angle () const {
        return (atan2 (a.y, a.x) < 0 ? atan2 (a.y, a.x) + pi * 2 : atan2 (a.y, a.x));
    }
    long double length () const {
        return hypotl (a.x, a.y);
    }
    friend ostream& operator<< (ostream& out, const Vector rhs) {
        out << rhs.a;
        return out;
    }
    friend istream& operator>> (istream& in, Vector &rhs) {
        in >> rhs.a;
        return in;
    }
};

struct Polygon {
    vector <Point> p;
    Polygon ( ) { }
    Polygon (vector<Point> p): p(p) { }
    size_t size () const {
        return p.size();
    }
    Point& operator[] (size_t x) {
        return p[x];
    }
    long double area () {
        long double res = 0;
        size_t sz = size();
        for (size_t i = 0; i < sz; ++i) {
            Point& x = p[i];
            Point& y = (i ? p[i - 1] : p.back());
            res += (x.x - y.x) * (x.y + y.y);
        }
        return abs(res) / 2;
    }
};

long double angle (Vector a, Vector b) {
    return abs(atan2 (a % b, a * b));
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
