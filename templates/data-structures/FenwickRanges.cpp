/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief 1-INDEXED! Fenwick tree. get(idx) -> val on index idx. update(l, r, delta) -> add on [l; r]. 
 * 
 * @tparam T Type of elements
 */
template <
  typename T
>
struct FenwickRange {
  vector <T> tr;
  FenwickRange() { }
  FenwickRange(size_t size) {
    tr.assign(size + 2, 0);
  }
  void update(int idx, T delta) {
    for(++idx; idx < tr.size(); idx += idx & -idx)
      tr[idx] += delta;
  }
  void update(int l, int r, T delta) {
    update(l, delta);
    update(r + 1, -delta);
  }
  T get(long long r) {
    if(r <= 0)
      return 0;
    T res = 0;
    for(++r; r > 0; r -= r & -r)
      res += tr[r];
    return res;
  }
};

/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief 1-INDEXED! Fenwick tree. get(l, r) -> sum on [l; r]. update(l, r, delta) -> add on [l; r]. 
 * 
 * @tparam T Type of elements
 */
template <
  typename T
>
struct FenwickRanges {
  FenwickRange<T> G1, G2;
  FenwickRanges(size_t size) {
    G1 = FenwickRange<T>(size);
    G2 = FenwickRange<T>(size);
  }
  void update(int l, int r, int delta) {
    G1.update(l, r, delta);
    G2.update(l, delta * (l - 1));
    G2.update(r + 1, -delta * r);
  }
  T get(int r) {
    return G1.get(r) * r - G2.get(r);
  }
  T get(int l, int r) {
    return get(r) - get(l - 1);
  }
};
