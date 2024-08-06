/**
 * Descripcion: basado en la clasificacion de aristas por medio del
 * arbol de dfs, donde una arista es puente si no existe un back-edge
 * que cruce por encima, los puntos de articulacion se obtienen de
 * forma similar. Retorna los puentes y un vector donde
 * art[i] = 1 si el i-esimo nodo es un punto de articulacion.
 * Tiempo: O(V + E)
 */

pair<vector<pi>, vi> findBridgesAndArticulationPoints(vector<vi>& g) {
  int n = SZ(g), t = 0;
  vector<pi> bridges;
  vi tin(n, -1), low(n, -1), art(n);
  auto dfs = [&](auto self, int u, int p = -1) -> void {
    tin[u] = low[u] = t++;
    int children = 0;
    for (int v : g[u]) if (v != p) {
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
        continue;
      }
      self(self, v, u);
      if (low[v] >= tin[u] && p != -1) art[u] = 1;
      if (low[v] > tin[u]) bridges.pb(u, v);
      low[u] = min(low[u], low[v]);
      children++;
    }
    if (p == -1 && children > 1) art[u] = 1;
  };
  FOR (u, 0, n) if (tin[u] == -1) dfs(dfs, u);
  return {bridges, art};
}
