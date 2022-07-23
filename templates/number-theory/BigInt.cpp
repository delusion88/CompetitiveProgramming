const int base = 1'000'000'000;
const int fft_base = 1'000;
const int base_digits = 9;
const int fft_base_digits = 3;

const double pi = acos(-1);

class BigInt {
 public:
  vector<int> digits;
  int sign = 1;


  BigInt() : sign(1) {}

  inline void trim() {
    while(digits.size() && digits.back() == 0) {
      digits.pop_back();
    }
    if(digits.size() == 0)
      sign = 1;
  }

  inline bool is_zero() const {
    return !digits.size(); 
  }

  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  BigInt(const T& val) {
    *this = val;
  }

  BigInt& operator= (long long val) {
    if(val >= 0) {
      sign = 1;
    } else {
      sign = -1;
      val = -val;
    }
    digits.clear();
    for(; val > 0; val /= base) {
      digits.push_back(val % base);
    }
    return *this;
  }

  BigInt(const string& s) {
    assert(!s.empty());
    sign = 1;
    int idx = 0;
    if(s[0] == '-') {
      sign = -1;
      idx = 1;
    } else if (s[0] == '+') {
      idx = 1;
    }
    for(int i = (int)s.size() - 1; i >= idx; i -= base_digits) {
      int x = 0;
      for(int j = max(idx, i - base_digits + 1); j <= i; ++j) {
        x = x * 10 + s[j] - '0';
      }
      digits.push_back(x);
    }
    trim();
  }

  friend istream& operator>> (istream& stream, BigInt& val) {
    string s;
    stream >> s;
    val = s;
    return stream;
  }

  friend ostream& operator<< (ostream& stream, BigInt val) {
    if(val.sign == -1 && !val.is_zero()) {
      stream << '-';
    } else if(val.is_zero()) {
      stream << 0;
      return stream;
    }
    stream << val.digits.back();
    for(int i = (int)val.digits.size() - 2; i >= 0; --i) {
      stream << setw(base_digits) << setfill('0') << val.digits[i];
    }
    return stream;
  }

  friend bool operator< (const BigInt& lhs, const BigInt& rhs) {
    if(lhs.sign != rhs.sign) {
      return lhs.sign < rhs.sign;
    }
    if(lhs.digits.size() != rhs.digits.size()) {
      return lhs.digits.size() * lhs.sign < rhs.digits.size() * rhs.sign;
    }
    for(int i = (int)lhs.digits.size() - 1; i >= 0; --i) {
      if(lhs.digits[i] != rhs.digits[i]) {
        return lhs.digits[i] * lhs.sign < rhs.digits[i] * rhs.sign;
      }
    }
    return 0;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator< (const BigInt& lhs, const T& rhs) {
    return lhs < BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator< (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
  }

  friend bool operator> (const BigInt& lhs, const BigInt& rhs) {
    return rhs < lhs;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator> (const BigInt& lhs, const T& rhs) {
    return lhs > BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator> (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
  }

  friend bool operator<= (const BigInt& lhs, const BigInt& rhs) {
    return !(rhs < lhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator<= (const BigInt& lhs, const T& rhs) {
    return lhs <= BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator<= (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
  }

  friend bool operator>= (const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator>= (const BigInt& lhs, const T& rhs) {
    return lhs >= BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator>= (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
  }

  friend bool operator== (const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator== (const BigInt& lhs, const T& rhs) {
    return lhs == BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator== (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
  }

  friend bool operator!= (const BigInt& lhs, const BigInt& rhs) {
    return (lhs < rhs) || (rhs < lhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator!= (const BigInt& lhs, const T& rhs) {
    return lhs != BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend bool operator!= (const T& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
  }

  BigInt operator-() const {
    BigInt res = *this;
    if (is_zero()) 
      return res;
    res.sign = -sign;
    return res;
  }

  inline static int __cmp_abs(const BigInt& lhs, const BigInt& rhs) {
    if(lhs.digits.size() != rhs.digits.size()) {
      return lhs.digits.size() < rhs.digits.size() ? -1 : 1;
    }
    for(int i = (int)lhs.digits.size() - 1; i >= 0; --i) {
      if(lhs.digits[i] != rhs.digits[i]) {
        return lhs.digits[i] < rhs.digits[i] ? -1 : 1;
      }
    }
    return 0;
  }

  inline void __add_nosign(const BigInt& val) {
    if(digits.size() < val.digits.size()) {
      digits.resize(val.digits.size(), 0);
    }
    int carry = 0;
    for(int i = 0; i < (int)max(val.digits.size(), digits.size()) || carry; ++i) {
      if(i == (int)digits.size())
        digits.emplace_back();
      digits[i] += carry + (i < (int)val.digits.size() ? val.digits[i] : 0);
      carry = digits[i] >= base;
      if(carry)
        digits[i] -= base;
    }
  }

  inline void __sub_nosign(const BigInt& val) {
    int carry = 0;
    for(int i = 0; i < (int)val.digits.size() || carry; ++i) {
      digits[i] -= carry + (i < (int)val.digits.size() ? val.digits[i] : 0);
      carry = digits[i] < 0;
      if(carry)
        digits[i] += base;
    }
    this->trim();
  }

  BigInt& operator+= (const BigInt& other) {
    if(sign == other.sign) {
      __add_nosign(other);
    } else {
      if (__cmp_abs(*this, other) >= 0) {
        __sub_nosign(other);
      } else {
        BigInt tmp = other;
        swap(*this, tmp);
        __sub_nosign(tmp);
      }
    }
    return *this;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  BigInt& operator+= (const T& other) {
    *this += BigInt(other);
    return *this;
  }

  BigInt& operator-= (const BigInt& other) {
    if(sign == other.sign) {
      if (__cmp_abs(*this, other) >= 0) {
        __sub_nosign(other);
      } else {
        BigInt tmp = other;
        swap(*this, tmp);
        __sub_nosign(tmp);
        this->sign = -this->sign;
      }
    } else {
      __add_nosign(other);
    }
    return *this;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  BigInt& operator-= (const T& other) {
    *this -= BigInt(other);
    return *this;
  }

  friend BigInt operator+ (BigInt lhs, BigInt rhs) {
    return lhs += rhs;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend BigInt operator+ (BigInt lhs, T rhs) {
    return lhs += BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend BigInt operator+ (T lhs, BigInt rhs) {
    BigInt tmp = lhs;
    return tmp += rhs;
  }

  friend BigInt operator- (BigInt lhs, BigInt rhs) {
    return lhs -= rhs;
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend BigInt operator- (BigInt lhs, T rhs) {
    return lhs -= BigInt(rhs);
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>>
  friend BigInt operator- (T lhs, BigInt rhs) {
    BigInt tmp = lhs;
    return tmp -= rhs;
  }

  void operator*=(int other) {
    if(abs(other) >= base) {
      *this *= BigInt(other);
      return;
    }
    if(other < 0)
      sign = -sign, other = -other;
    int carry = 0;
    for(int i = 0; i < (int)digits.size() || carry; ++i) {
      if (i == (int)digits.size())
        digits.emplace_back();
      long long cur = digits[i] * (long long)other + carry;
      carry = (int)(cur / base);
      digits[i] = (int)(cur % base);
    }
    trim();
  }

  friend BigInt operator* (BigInt lhs, int rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend BigInt operator* (int lhs, BigInt rhs) {
    rhs *= lhs;
    return rhs;
  }

  inline static vector<int> convert_base(const vector<int>& digits, int from, int to) {
    vector<long long> pows(max(from, to) + 1);
    pows[0] = 1;
    for(int i = 1; i < pows.size(); ++i)
      pows[i] = (pows[i - 1] * 10ll);
    vector<int> res;
    long long cur = 0;
    int cur_digits = 0;
    for(int i = 0; i < (int)digits.size(); ++i) {
      cur += digits[i] * pows[cur_digits];
      cur_digits += from;
      while(cur_digits >= to) {
        res.push_back(cur % pows[to]);
        cur /= pows[to];
        cur_digits -= to;
      }
    }
    res.push_back(cur);
    while(res.size() && res.back() == 0)
      res.pop_back();
    return res;
  }

  inline static void fft(vector<complex<double>>& x, int inv) {
    assert(inv * inv == 1);

    int n = x.size();
    for(int i = 1, j = 0; i < n; ++i) {
      int bit = n >> 1;
      for(; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;
      if(i < j)
        swap(x[i], x[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
      double angle = 2 * pi / len * inv;
      complex<double> wlen(cos(angle), sin(angle));
      for(int i = 0; i < n; i += len) {
        complex<double> w(1);
        for(int j = 0; j < len / 2; ++j) {
          complex<double> u = x[i + j], 
                          v = x[i + j + (len >> 1)] * w;
          x[i + j] = u + v;
          x[i + j + (len >> 1)] = u - v;
          w *= wlen;
        }
      }
    }

    if(inv < 0) {
      for(auto& e : x)
        e /= n;
    }
  }

  inline void __multiply(const vector<int>& x, const vector<int>& y, vector<int>& res) const {
    vector<complex<double>> a(x.begin(), x.end());
    vector<complex<double>> b(y.begin(), y.end());
    int n = 1;
    while(n < (int)max(x.size(), y.size())) {
      n <<= 1;
    }
    n <<= 1;
    a.resize(n);
    b.resize(n);
    fft(a, 1);
    fft(b, 1);
    for(int i = 0; i < n; ++i)
      a[i] *= b[i];
    fft(a, -1);
    res.resize(n);
    long long carry = 0;
    for(int i = 0; i < n; ++i) {
      long long tmp = (long long)round(a[i].real()) + carry;
      carry = tmp / fft_base;
      res[i] = tmp % fft_base;
    }
  }

  BigInt multiply_fft(const BigInt& other) const {
    BigInt res;
    res.sign = sign * other.sign;
    __multiply(convert_base(digits, base_digits, fft_base_digits), 
               convert_base(other.digits, base_digits, fft_base_digits), 
               res.digits);
    res.digits = convert_base(res.digits, fft_base_digits, base_digits);
    res.trim();
    return res;
  }

  void operator*= (const BigInt& other) {
    *this = (*this * other);
  }

  BigInt operator* (const BigInt& rhs) const {
    return multiply_fft(rhs);
  }
  friend BigInt operator* (const BigInt& lhs, const long long& rhs) {
    return lhs * BigInt(rhs);
  }
  friend BigInt operator* (const long long& lhs, const BigInt& rhs) {
    return rhs * BigInt(lhs);
  }

  inline friend pair<BigInt, BigInt> divmod(const BigInt& x, const BigInt& y) {
    assert(!y.is_zero());

    if(y < 0) {
      return make_pair(divmod(-x, -y).first, -divmod(-x, -y).second);
    }

    int norm = base / (y.digits.back() + 1);
    BigInt a = abs(x) * norm;
    BigInt b = abs(y) * norm;
    BigInt q = 0, r = 0;
    q.digits.resize((int)a.digits.size());
    for(int i = (int)a.digits.size() - 1; i >= 0; --i) {
      r *= base;
      r += a.digits[i];
      long long s1 = (int)r.digits.size() <= (int)b.digits.size() ? 0 : r.digits[(int)b.digits.size()];
      long long s2 = (int)r.digits.size() <= (int)b.digits.size() - 1 ? 0 : r.digits[(int)b.digits.size() - 1];
      long long d = ((long long)base * s1 + s2) / b.digits.back();
      r -= b * d;
      while(r < 0) {
        r += b, --d;
      }
      q.digits[i] = d;
    }
    q.sign = x.sign * y.sign;
    r.sign = x.sign;
    q.trim();
    r.trim();
    return make_pair(q, (r / norm) < 0 ? (r / norm) + y : (r / norm));
  }
  BigInt operator/ (const BigInt& other) const {
    return divmod(*this, other).first;
  }
  friend BigInt operator/ (const BigInt& lhs, const long long& rhs) {
    return lhs / BigInt(rhs);
  }
  BigInt operator% (const BigInt& other) const {
    return divmod(*this, other).second;
  }
  friend BigInt operator% (const BigInt& lhs, const long long& rhs) {
    return lhs % BigInt(rhs);
  }

  void operator/= (const BigInt& other) {
    *this = *this / other;
  }
  void operator/= (const long long& other) {
    *this = *this / BigInt(other);
  }
  void operator%= (const BigInt& other) {
    *this = *this % other;
  }
  void operator%= (const long long& other) {
    *this = *this % BigInt(other);
  }

  void operator/= (int other) {
    assert(other > 0);
    if(abs(other) >= base) {
      *this /= BigInt(other);
      return;
    }
    for(int i = (int)digits.size() - 1, rem = 0; i >= 0; --i) {
      long long cur = digits[i] + rem * (long long)base;
      digits[i] = (int)(cur / other);
      rem = (int)(cur % other);
    }
    trim();
  }
  BigInt operator/ (int other) const {
    assert(other > 0);
    if(abs(other) >= base) {
      return *this / BigInt(other);
    }
    BigInt res = *this;
    res /= other;
    return res;
  }

  inline friend BigInt abs(BigInt x) {
    x.sign = 1;
    return x;
  }
};
