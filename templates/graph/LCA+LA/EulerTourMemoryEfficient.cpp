/**
 * @date 2022-07-23
 * @author Delusion88
 */
class LCA {
 private:
  vector<vector<int>> g_;

  vector<int> fst_, lst_, seg_, transform_, reverse_, eul_;

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
  
  void build_st(int x, int l, int r) {
    if(l == r) {
      seg_[x] = eul_[l];
      return;
    }
    build_st(x * 2 + 1, l, (l + r) / 2);
    build_st(x * 2 + 2, (l + r) / 2 + 1, r);
    seg_[x] = min(seg_[x * 2 + 1], seg_[x * 2 + 2]);
  }

  int get_st(int x, int l, int r, int ql, int qr) {
    if(l >= ql && r <= qr) {
      return seg_[x];
    }
    int tmp = Inf;
    if((l + r) / 2 >= ql) {
      tmp = min(tmp, get_st(x * 2 + 1, l, (l + r) / 2, ql, qr));
    }
    if((l + r) / 2 + 1 <= qr) {
      tmp = min(tmp, get_st(x * 2 + 2, (l + r) / 2 + 1, r, ql, qr));
    }
    return tmp;
  }

  void build(int n, int root) {
    for(int i = 0; i < n; ++i)
      g[i].shrink_to_fit();
    g_.resize(n, vector<int>());
    fst_.assign(n, -1);
    lst_.assign(n, -1);
    transform_.resize(n);
    reverse_.resize(n);
    timer = 0;
    eul_.clear();
    rebuild_dfs(root, -1);
    for(int i = 0; i < n; ++i)
      g_[i].shrink_to_fit();
    build_euler_tour(root, -1);
    eul_.shrink_to_fit();
    seg_.assign((1 << (2 + __lg(n) + (bool)(__builtin_popcount(n) - 1))) + 5, Inf);
    build_st(0, 0, eul_.size());
  }

  int get(int u, int v) {
    return transform_[get_st(0, 0, eul_.size(), min(fst_[reverse_[u]], lst_[reverse_[v]]), max(fst_[reverse_[u]], lst_[reverse_[v]]))];
  }
};
