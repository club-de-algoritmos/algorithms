/**
 * Descripcion: calcula el costo minimo para
 * ir desde un nodo hacia todos los demas.
 * Tiempo: O(E log V)
 */
vi dijkstra(vector<vector<pi>>& g, int x) {
  int n = SZ(g); vi d(n);
  FOR(i, 0, n) d[i] = INF;
  d[x] = 0;
  priority_queue<pi> pq; pq.emplace(0, x);
  while (!pq.empty()) {
    auto [du, u] = pq.top(); pq.pop();
    du *= -1;
    if (du > d[u]) continue;
    for (auto &[v, w]:g[u])if(du+w<d[v]){
      d[v] = du + w;
      pq.emplace(-d[v], v);
    }
  }
  return d;
}
// Para tener a lo mucho V elementos en la PQ
vi dijkstra(vector<vector<pi>>& g, int st) {
  int n = SZ(g); vi d(n);
  set<pi> pq;
  FOR(i,0,n)pq.emplace(d[i], i),d[i]=INF;
  while (!pq.empty()) {
    auto [du, u] = *pq.begin(); pq.erase(pq.begin());
    for (auto &[v, w] : g[u])if(du+w<d[v]){
      pq.erase(pq.find({d[v], v}));
      d[v] = du + w;
      pq.emplace(d[v], v);
    }
  }
  return d;
}
