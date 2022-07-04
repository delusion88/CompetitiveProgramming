/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Class for storing lines for CHT
 */
class LineContainer {
 private:
  class line {
   public:
    mutable long long k, b, p;
    line() : k(0), b(0), p(inf) { }
    line(long long _k, long long _b) : k(_k), b(_b), p(inf) { }
    bool operator<(const line &l) const {
      return k < l.k;
    }
    bool operator<(const long long &x) const {
      return p < x;
    }
    long long operator()(long long x) const {
      return k * x + b;
    }
  };
  multiset<line, less<>> st;
  long long div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool intersect(multiset<line>::iterator x, multiset<line>::iterator y) {
    if(y == st.end()) {
      x->p = inf;
      return false;
    }
    if(x->k == y->k) {
      x->p = x->b > y->b ? inf : -inf;
    } else {
      x->p = div(y->b - x->b, x->k - y->k);
    }
    return x->p >= y->p;
  }
 public:
  void add(long long k, long long b) {
    auto x = st.insert({k, b}), y = x, z = x;
    z++;
    while(intersect(y, z)) {
      z = st.erase(z);
    }
    if(x != st.begin() && intersect(--x, y)) {
      intersect(x, st.erase(y));
    }
    while((y = x) != st.begin() && (--x)->p >= y->p) {
      intersect(x, st.erase(y));
    }
  }
  long long query(long long x){
    return(*st.lower_bound(x))(x);
  }
  void clear(){
    st.clear();
  }
};
