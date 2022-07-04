/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Find shortest paths from s to all vertices in the graph. Negative weights supported.
 */
void shortest_paths(int n, int s, vector<long long>& d) {
  d.assign(n, inf);
  d[s] = 0;
  vector<long long> m(n, 2);
  deque<long long> q;
  q.push_back(s);
  while(!q.empty()) {
    int u = q.front();
    q.pop_front();
    m[u] = 0;
    for(auto [to, w] : g[u]) {
      if(d[to] > d[u] + w) {
        d[to] = d[u] + w;
        if(m[to] == 2) {
          m[to] = 1;
          q.push_back(to);
        } else if(m[to] == 0) {
          m[to] = 1;
          q.push_front(to);
        }
      }
    }
  }
}
