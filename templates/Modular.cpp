const long long mod = 1000000007;

struct Modular {
    long long val;
    
    Modular (long long x) {
        if (x < 0) {
            x %= mod;
            x += mod;
            x %= mod;
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
