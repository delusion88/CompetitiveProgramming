struct MaxMerger {
  template <
    typename T
  > 
  void operator()(T& res, T& a, T& b) const {
    res = max(a, b);
  }
};

/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Segment Tree
 * 
 * @tparam T Type of elements
 * @tparam Merge Merger
 */
template <typename T, typename Merge = MaxMerger>
class SegmentTree {
 private:
  int n;
  T neutral;
  Merge merge;
  vector<T> tr;
 public:
  SegmentTree(int n, T neutral): n(n), neutral(neutral) {
    tr.assign(4 * n + 5, neutral);
    merge = Merge();
  }
  T _get(int node, int l, int r, int ql, int qr) {
    if(l >= ql && r <= qr) {
      return tr[node];
    }
    if(l > qr || r < ql) {
      return neutral;
    }
    int m = (l + r) / 2;
    T a = _get(node * 2 + 1, l, m, ql, qr),
      b = _get(node * 2 + 2, m + 1, r, ql, qr),
      cur;
    merge(cur, a, b);
    return cur;
  }
  void _upd(int node, int l, int r, int ql, int qr, T val) {
    if(ql == l && qr == r) {
      tr[node] = val;
      return;
    }
    if(l > qr || r < ql) {
      return;
    }
    int m = (l + r) / 2;
    _upd(node * 2 + 1, l, m, ql, qr, val);
    _upd(node * 2 + 2, m + 1, r, ql, qr, val);
    merge(tr[node], tr[node * 2 + 1], tr[node * 2 + 2]);
  }
  int _gr(int node, int l, int r, int ql, int qr, T val) {
    if(l > qr || r < ql) 
      return Inf;
    if(ql <= l && r <= qr) {
      if(tr[node] < val) 
        return Inf;
      while(r - l > 0) {
        int mid = (r + l) / 2;
        if(tr[2 * node + 1] >= val) {
          node = 2 * node + 1;
          r = mid;
        } else {
          node = 2 * node + 2;
          l = mid + 1;
        }
      }
      return l;
    }
    int mid = (l + r) / 2;
    return min( _gr(2 * node + 1, l, mid, ql, qr, val),
          _gr(2 * node + 2, mid + 1, r, ql, qr, val));
  }
  T get(int l, int r) {
    return _get(0, 0, n - 1, l, r);
  }
  void update(int idx, T val) {
    _upd(0, 0, n - 1, idx, idx, val);
  }
  /**
   * @brief Find nearest to the right of l greater than val
   * 
   * @param Merge Must be MaxMerger
   * @param l Position
   * @param val Value
   * @return Position of element >= val 
   */
  int greater_r(int l, T val) {
    T ans = _gr(0, 0, n - 1, l, n - 1, val + 1);
    return ans == Inf ? -1 : ans;
  }
};
