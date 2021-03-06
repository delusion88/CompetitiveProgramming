struct SPMaxMerger {
  template <
    typename T
  > 
  T operator()(T a, T b) const {
    return max(a, b);
  }
};

/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Sparse table
 * 
 * @tparam T Type of elements
 * @tparam SPMerge Merger
 */
template <typename T, typename SPMerge = SPMaxMerger>
class SparseTable {
 private:
  size_t size, k;
  vector<vector<T>> sparse;
  SPMerge merge;
 public:
  SparseTable(): merge(SPMerge()) { }
  SparseTable(size_t size): merge(SPMerge()), size(size), k(__lg(size) + 1) {
    sparse.assign(k, vector<T>(size));
  } 
  SparseTable(vector<T> v): merge(SPMerge()), size(v.size()), k(__lg(size) + 1) {
    sparse.assign(k, vector<T>(size, 0));  
    sparse[0] = v;  
    for(int l = 1; l < k; ++l)
      for(int i = 0; i + (1 << l) <= size; ++i)
        sparse[l][i] = merge(sparse[l - 1][i], sparse[l - 1][i + (1 << (l - 1))]);
  }
  T get(int l, int r) {
    int lg = __lg(r - l + 1);
    return merge(sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
  }
};
