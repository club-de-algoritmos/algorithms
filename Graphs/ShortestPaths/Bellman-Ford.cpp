/**
 * Descripcion: calcula el costo minimo para ir de un nodo
 * hacia todos los demas alcanzables. Puede detectar ciclos
 * negativos, dando una ultima pasada y revisando si alguna
 * distancia se acorta.
 * Tiempo: O(VE)
 */

int main() {
  int n, m, A, B, W;
  cin >> n >> m;
  tuple<int, int, int> edges[m];
  for (int i = 0; i < m; i++) {
    cin >> A >> B >> W;
    edges[i] = make_tuple(A, B, W);
  }
  vi dist(n + 1, INF);

  int x;
  cin >> x;
  dist[x] = 0;  // Nodo de inicio
  for (int i = 0; i < n; i++) {
    for (auto e : edges) {
      auto [a, b, w] = e;
      dist[b] = min(dist[b], dist[a] + w);
    }
  }

  for (auto e : edges) {
    auto [u, v, weight] = e;
    if (dist[u] != INF && dist[u] + weight < dist[v]) {
      cout << "Graph contains negative weight cycle"
           << endl;
      return 0;
    }
  }

  cout << "Shortest distances from source " << x << ENDL;
  for (int i = 0; i < n; i++) {
    cout << (dist[i] == INF ? -1 : dist[i]) << " ";
  }

  return 0;
}
