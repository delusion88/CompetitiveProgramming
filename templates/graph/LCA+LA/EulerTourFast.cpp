/**
 * @date 2022-07-23
 * @author Delusion88
 */
class LCA {
 private:
  vector<vector<int>> g_;

  vector<int> fst_, lst_, transform_, reverse_, eul_;

  SparseTable<int> sp_ = SparseTable<int>();

  int timer = 0;

 public:
  void rebuild_dfs(int v, int p) {
    int cur = timer;
    transform_[cur] = v;
    reverse_[v] = cur;
    for(auto& e : g[v]) {
      if(e != p) {
        g_[cur].push_back(++timer);
        g_[timer].push_back(cur);
        rebuild_dfs(e, v);
      }
    }
  }

  void build_euler_tour(int v, int p) {
    if(fst_[v] == -1) {
      fst_[v] = eul_.size();
    }
    eul_.push_back(v);
    for(auto& e : g_[v]) {
      if(e != p) {
        build_euler_tour(e, v);
        eul_.push_back(v);
      }
    }
    lst_[v] = eul_.size() - 1;
  }
  
  void build(int n, int root) {
    g_.resize(n, vector<int>());
    fst_.assign(n, -1);
    lst_.assign(n, -1);
    transform_.resize(n);
    reverse_.resize(n);
    timer = 0;
    eul_.clear();
    rebuild_dfs(root, -1);
    build_euler_tour(root, -1);
    sp_ = SparseTable<int>(eul_);
  }

  int get(int u, int v) {
    return transform_[sp_.get(min(fst_[reverse_[u]], lst_[reverse_[v]]), max(fst_[reverse_[u]], lst_[reverse_[v]]))];
  }
};
