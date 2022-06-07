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
