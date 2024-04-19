/**
 * Descripcion: calcula el costo minimo para ir de un nodo
 * hacia todos los demas alcanzables.
 * Tiempo: O(E log V)
 */

vector<pi> graph[MAXN];
int dist[MAXN];

// O(V + E log V)
void dijkstra(int x) {
  FOR(i, 0, MAXN)
  dist[i] = INF;
  dist[x] = 0;

  priority_queue<pi> pq;
  pq.emplace(0, x);
  while (!pq.empty()) {
    auto [du, u] = pq.top();
    du *= -1;
    pq.pop();

    if (du > dist[u]) continue;

    for (auto &[v, dv] : graph[u]) {
      if (du + dv < dist[v]) {
        dist[v] = du + dv;
        pq.emplace(-dist[v], v);
      }
    }
  }

  // Si la pq puede tener muchisimos elementos, utilizamos
  // un set, en donde habra a lo mucho V elementos
  set<pi> pq;
  for (int u = 0; u < V; ++u) pq.emplace(dist[u], u);

  while (!pq.empty()) {
    auto [du, u] = *pq.begin();
    pq.erase(pq.begin());
    for (auto &[v, dv] : graph[u]) {
      if (du + dv < dist[v]) {
        pq.erase(pq.find({dist[v], v}));
        dist[v] = du + dv;
        pq.emplace(dist[v], v);
      }
    }
  }
}
