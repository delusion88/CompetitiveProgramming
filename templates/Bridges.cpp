const int N = 300000;
vector<pair<int, int>> g[N];
int d[N], up[N];
vector<int> ans;
void dfs (int v, int p, int dep) {
  d[v] = up[v] = dep;
  for (auto e : g[v]) {
    if (e.first == p) continue;
    if (d[e.first] == 0) {
      dfs(e.first, v, dep + 1);
      up[v] = min(up[v], up[e.first]);
      if (up[e.first] >= d[e.first]) {
        ans.push_back(e.second);
      }
    }
    else {
      up[v] = min(up[v], d[e.first]);
    }
  }
}
