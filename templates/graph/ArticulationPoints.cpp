/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Find articulation points in a graph
 */
const int maxn = 300000;
int d[maxn], up[maxn], ans[maxn];
void dfs(int v, int p, int dep) {
  d[v] = up[v] = dep;
  int ch = 0;
  for(auto e : g[v]) {
    if(e == p) continue;
    if(!d[e]) {
      dfs(e, v, dep + 1);
      up[v] = min(up[v], up[e]);
      if(d[v] <= up[e] && p != -1) {
        ans[v] = 1;
      }
      ch++;
    } else {
      up[v] = min(up[v], d[e]);
    }
  }
  if(p == -1 && ch > 1) {
    ans[v] = 1;
  }
}
