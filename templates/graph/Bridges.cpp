/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Find bridges in a graph
 * 
 * @attention All edges in graph: g[from] {to; number}
 */
const int maxn = 300000;
int d[maxn], up[maxn];
vector<int> ans;
void dfs(int v, int p, int dep) {
  d[v] = up[v] = dep;
  for(auto e : g[v]) {
    if(e.first == p) continue;
    if(d[e.first] == 0) {
      dfs(e.first, v, dep + 1);
      up[v] = min(up[v], up[e.first]);
      if(up[e.first] >= d[e.first]) {
        ans.push_back(e.second);
      }
    } else {
      up[v] = min(up[v], d[e.first]);
    }
  }
}
