/**
 * @date 2022-07-23
 * @author Delusion88
 */

const int maxn = 1000000, maxlg = 23;

vector<int> g[maxn];

int tin[maxn], tout[maxn], timer, lg;
int up[maxlg][maxn];

void dfs_binup(int v, int p) {
  tin[v] = timer++;
  up[0][v] = p;
  for(int i = 1; i <= lg; ++i) {
    up[i][v] = up[i - 1][up[i - 1][v]];
  }
  for(auto e : g[v]) {
    if(e != p) {
      dfs_binup(e, v);
    }
  }
  tout[v] = timer++;
}

inline bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

/**
 * @brief find level ancestor O(log(n))
 * 
 * @param u vertex
 * @param k level
 */
inline int la(int u, int k) {
  for(int i = lg; i >= 0; --i) {
    if(k & (1 << i)) {
      u = up[i][u];
    }
  }
  return u;
}

/**
 * @brief find lowest common ancestor O(log(n))
 * 
 * @param u first vertex
 * @param v second vertex
 */
inline int lca(int u, int v) {
  if(is_ancestor(u, v))
    return u;
  if(is_ancestor(v, u))
    return v;
  for(int i = lg; i >= 0; --i) {
    if(!is_ancestor(up[i][u], v)) {
      u = up[i][u];
    }
  }
  return up[0][u];
}

/**
 * @brief solve dynamic LCA problem
 * 
 * @param r root
 * @param u first vertex
 * @param v second vertex
 */
inline int dynamic_lca(int r, int u, int v) {
  return lca(u, v) ^ lca(u, r) ^ lca(r, v);
}

/**
 * @brief O(n*log(n))
 */
void precalc_binup(int root = 0, int n = maxn) {
  memset(tin, 0, (sizeof tin[0]) * n);
  memset(tout, 0, (sizeof tout[0]) * n);
  for(int i = 0; i < maxlg; ++i)
    memset(up[i], 0, (sizeof up[i][0]) * n);
  timer = 0;
  lg = __lg(n) + (bool)(__builtin_popcount(n) - 1);
  dfs_binup(root, root);
}
