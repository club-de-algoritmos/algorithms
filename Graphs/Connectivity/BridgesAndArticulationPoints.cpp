/**
 * Descripcion: algoritmo para buscar los puentes y puntos
 * de articulacion en un grafo, regresa un par (P, A) donde
 * P contiene a las aristas que son un puente y A contiene
 * los nodos que son un punto de articulacion, si se
 * requiere un vector<bool> A(n), donde A[i] indica si el
 * i-esimo nodo es un punto de articulacion, retornar
 * articulation.
 * Tiempo: O(V + E)
 */

pair<vector<pi>, vi> findBridgesAndArticulationPoints(
    vector<vi>& g) {
  int n = SZ(g), timer = 0;
  vector<pi> bridges;
  vi tin(n, -1), low(n, -1);
  vector<bool> articulation(n, 0);
  auto dfs = [&](auto self, int u, int p = -1) -> void {
    tin[u] = low[u] = timer++;
    int children = 0;
    for (int v : g[u]) {
      if (v == p) continue;
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
        continue;
      }
      self(self, v, u);
      if (low[v] >= tin[u] && p != -1) articulation[u] = 1;
      if (low[v] > tin[u]) bridges.pb({u, v});
      low[u] = min(low[u], low[v]);
      children++;
    }
    if (p == -1 && children > 1) articulation[u] = 1;
  };
  FOR(u, 0, n) if (tin[u] == -1) dfs(dfs, u);
  vi articulationPoints;
  FOR(u, 0, n)
  if (articulation[u]) articulationPoints.pb(u);
  return {bridges, articulationPoints};
}
