/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Fenwick tree. get(l, r) -> sum on [l; r]
 * 
 * @tparam T Type of elements
 */
template <typename T>
class Fenwick {
 private:
  vector<T> tr;
 public:
  Fenwick(size_t size) {
    tr.assign(size, 0);
  }
  void update(size_t idx, T delta) {
    for(; idx < tr.size(); idx |= idx + 1)
      tr[idx] += delta;
  }
  T get(long long r) {
    if(r < 0)
      return 0;
    T res = 0;
    for(++r; r > 0; r &= r - 1)
      res += tr[r - 1];
    return res;
  }
  T get(long long l, long long r) {
    return get(r) - get(l - 1);
  }
};
