/**
 * Descripcion: Algoritmo simple para maximo emparejamiento bipartito.
 * el grafo g debe de ser una lista de los vecinos de la particion
 * izquierda y m el numero de nodos en la particion derecha.
 * Retorna (|matching|, btoa) donde btoa[i] sera el
 * emparejamiento para el vertice i del lado derecho o -1 si no lo tiene
 * Tiempo: O(VE)
 */
pair<int, vi> kuhn(vector<vi>& g, int m) {
  vi vis, btoa(m, -1);
  auto dfs = [&](auto self, int j) -> bool {
    if (btoa[j] == -1) return 1;
    vis[j] = 1;
    int di = btoa[j];
    for (int e : g[di]) if (!vis[e] && self(self, e)) {
      btoa[e] = di;
      return 1;
    }
    return 0;  
  };
  FOR (i, 0, SZ(g)) {
    vis.assign(SZ(btoa), 0);
    for (int j : g[i]) if (dfs(dfs, j)) {
      btoa[j] = i;
      break;
    }
  }
  return {SZ(btoa) - (int)count(ALL(btoa), -1), btoa};
}
