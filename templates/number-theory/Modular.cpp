/**
 * @date 2022-07-04
 * @author Delusion88
 */
const long long mod = 1000000007;
class Modular {
 public:
  Modular() : val() {}
  template <typename T>
  Modular(const T& x) { val = normalize(x); }

  template <typename T>
  static long long normalize(const T& x) {
    long long v;
    if(-mod <= x && x < mod) v = static_cast<long long>(x);
    else v = static_cast<long long>(x % mod);
    if(v < 0) v += mod;
    return v;
  }

  const long long& operator()() const { return val; }
  template <typename T>
  explicit operator T() const { return static_cast<T>(val); }

  Modular& operator+=(const Modular& other) { if((val += other.val) >= mod) val -= mod; return *this; }
  template <typename T> 
  Modular& operator+=(const T& other) { return *this += Modular(other); }
  friend Modular operator+(const Modular& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }
  template <typename T>
  friend Modular operator+(const Modular& lhs, const T& rhs) { return Modular(lhs) += rhs; }
  template <typename T>
  friend Modular operator+(const T& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }
  Modular& operator++() { return *this += 1; }

  Modular& operator-=(const Modular& other) { if((val -= other.val) < 0) val += mod; return *this; }
  template <typename T> 
  Modular& operator-=(const T& other) { return *this -= Modular(other); }
  friend Modular operator-(const Modular& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }
  template <typename T>
  friend Modular operator-(const Modular& lhs, const T& rhs) { return Modular(lhs) -= rhs; }
  template <typename T>
  friend Modular operator-(const T& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }
  Modular& operator--() { return *this -= 1; }
  Modular operator-() const { return Modular(-val); }

  Modular& operator*=(const Modular& other) {     
    val = normalize(static_cast<long long>(val) * static_cast<long long>(other.val));
    return *this; 
  }
  template <typename T>
  Modular& operator*=(const T& other) { return *this *= Modular(other); }
  friend Modular operator*(const Modular& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }
  template <typename T>
  friend Modular operator*(const Modular& lhs, const T& rhs) { return Modular(lhs) *= rhs; }
  template <typename T>
  friend Modular operator*(const T& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }

  Modular& operator/=(const Modular& other) { return (*this) *= Modular(inverse(other(), mod)); }
  template <typename T>
  Modular& operator/=(const T& other) { return *this /= Modular(other); }
  friend Modular operator/(const Modular& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }
  template <typename T>
  friend Modular operator/(const Modular& lhs, const T& rhs) { return Modular(lhs) /= rhs; }
  template <typename T>
  friend Modular operator/(const T& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }

  template <typename T>
  Modular& operator%=(const T& other) { (this->val %= other); return *this; }
  template <typename T>
  friend Modular operator%(const Modular& lhs, const T& rhs) { return Modular(lhs) %= rhs; }

  template <typename T>
  static T inverse(const T& a_, const T& m_) {
    T a = a_, m = m_;
    T u = 0, v = 1;
    while(a != 0) {
      T t = m / a;
      m -= t * a; 
      swap(a, m);
      u -= t * v; 
      swap(u, v);
    }
    assert(m == 1);
    return u;
  }

  friend const long long& abs(const Modular& x) { return x(); }

  friend ostream& operator<<(ostream& out, const Modular& rhs) {
    out << rhs();
    return out;
  }
  friend istream& operator>>(istream& in, Modular &rhs) {
    long long x;
    in >> x;
    rhs = x;
    return in;
  }

  friend bool operator==(const Modular& lhs, const Modular& rhs) { return lhs() == rhs(); }
  template <typename T> friend bool operator==(const Modular& lhs, T rhs) { return lhs == Modular(rhs); }
  template <typename T> friend bool operator==(T lhs, const Modular& rhs) { return Modular(lhs) == rhs; }
  
  friend bool operator!=(const Modular& lhs, const Modular& rhs) { return !(lhs == rhs); }
  template <typename T> friend bool operator!=(const Modular& lhs, T rhs) { return !(lhs == rhs); }
  template <typename T> friend bool operator!=(T lhs, const Modular& rhs) { return !(lhs == rhs); }

  friend bool operator<(const Modular& lhs, const Modular& rhs) { return lhs() < rhs(); }
  template <typename T> friend bool operator<(const Modular& lhs, T rhs) { return lhs < Modular(rhs); }
  template <typename T> friend bool operator<(T lhs, const Modular& rhs) { return Modular(lhs) < rhs; }

  friend bool operator<=(const Modular& lhs, const Modular& rhs) { return (lhs < rhs) || (lhs == rhs); }
  template <typename T> friend bool operator<=(const Modular& lhs, T rhs) { return (lhs < rhs) || (lhs == rhs); }
  template <typename T> friend bool operator<=(T lhs, const Modular& rhs) { return (lhs < rhs) || (lhs == rhs); }

  friend bool operator>(const Modular& lhs, const Modular& rhs) { return !(lhs <= rhs); }
  template <typename T> friend bool operator>(const Modular& lhs, T rhs) { return !(lhs <= rhs); }
  template <typename T> friend bool operator>(T lhs, const Modular& rhs) { return !(lhs <= rhs); }

  friend bool operator>=(const Modular& lhs, const Modular& rhs) { return !(lhs < rhs); }
  template <typename T> friend bool operator>=(const Modular& lhs, T rhs) { return !(lhs < rhs); }
  template <typename T> friend bool operator>=(T lhs, const Modular& rhs) { return !(lhs < rhs); }

 private:
  long long val;
};

template <typename T>
Modular power(const Modular& x_, const T& p_) {
  assert(p_ >= 0);
  Modular x = x_, res = 1;
  T p = p_;
  while(p > 0) {
    if(p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

string to_string(const Modular& x) {
  return to_string(x());
}

Modular sqrt(const Modular& a) {
  if(a == 0) 
    return 0;
  assert(power(a, (mod - 1) / 2) == 1);
  if(mod % 4 == 3) 
    return power(a, (mod + 1) / 4);
  long long s = mod - 1, n = 2;
  long long r = 0, m;
  while(s % 2 == 0)
    ++r, s /= 2;
  while(power(n, (mod - 1) / 2) != mod - 1) 
    ++n;
  Modular x = power(a, (s + 1) / 2);
  Modular b = power(a, s), g = power(n, s);
  for(;; r = m) {
    Modular t = b;
    for(m = 0; m < r && t != 1; ++m)
      t = t * t % mod;
    if(m == 0) 
      return x;
    Modular gs = power(g, 1LL << (r - m - 1));
    g = gs * gs % mod;
    x = x * gs % mod;
    b = b * g % mod;
  }
}
