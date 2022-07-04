/**
 * @date 2022-06-?
 * @author Delusion88
 * @brief Find shortest paths from s to all vertices in the graph.
 */
vector<long long> dijkstra(int n, int s = 0) {
  vector<long long> d(n, inf);
  d[s] = 0;
  priority_queue<pair<long long, long long>, pair<long long, long long>, pair<long long, long long>> q;
  q.push(make_pair(0ll, s));
  while(!q.empty()) {
    auto [cur_d, v] = q.top();
    q.pop();
    if(cur_d > d[v])
      continue;
    for(auto [u, w] : g[v]) {
      if(d[u] > d[v] + w) {
        d[u] = d[v] + w;
        q.push(make_pair(d[u], u));
      }
    }
  }
}
