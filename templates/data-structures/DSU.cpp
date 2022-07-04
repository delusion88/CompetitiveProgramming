/**
 * @date 2022-?-?
 * @author Delusion88
 * @brief DSU Data structure
 */
class DSU {
 private:
  size_t size_;
  vector<int> p_;
 public:
  DSU() { }
  DSU(size_t size): size_(size) {
    p_.resize(size_);
    iota(p_.begin(), p_.end(), 0);
  }
  size_t size() {
    return size_;
  }
  int get(int v) {
    return(v == p_[v]) ? v : p_[v] = get(p_[v]);
  }
  void unite(int u, int v) {
    u = get(u);
    v = get(v);
    if(u == v)
      return;
    p_[v] = u;
  }
};
