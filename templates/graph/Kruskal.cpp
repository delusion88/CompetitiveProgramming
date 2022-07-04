class edge {
 public:
  long long u, v, w;
};
/**
 * @date 2022-07-04
 * @author Delusion88
 * @brief Find MST in the undirected graph
 * 
 * @param edges Edges of graph 
 * @param n Number of vertices
 * @return pair<long long, vector<edge>> {cost, path}
 */
pair<long long, vector<edge>> Kruskal(vector<edge> edges, int n) {
  sort(edges.begin(), edges.end(), [&](edge a, edge b) { return a.w < b.w; });
  DSU dsu(n);
  long long ans = 0;
  vector<edge> res;
  for(auto& e : edges) {
    if(dsu.get(e.u) != dsu.get(e.v)) {
      dsu.unite(e.u, e.v);
      ans += e.w;
      res.push_back(e);
    }
  }
  return make_pair(ans, res);
}
