const int N = 300000;
vector<int> g[N];
int d[N], up[N];
set<int> ans;
void dfs (int v, int p, int dep) {
  d[v] = up[v] = dep;
  int ch = 0;
  for (auto e : g[v]) {
    if (e == p) continue;
    if (!d[e]) {
      dfs(e, v, dep + 1);
      up[v] = min(up[v], up[e]);
      if (d[v] <= up[e] && p != -1) {
        ans.insert(v);
      }
      ch++;
    }
    else {
      up[v] = min(up[v], d[e]);
    }
  }
  if (p == -1 && ch > 1) {
    ans.insert(v);
  }
}
