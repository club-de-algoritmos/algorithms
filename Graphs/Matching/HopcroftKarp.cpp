/**
 * Descripcion: Algoritmo de Hopcroft-Karp para maximo emparejamiento bipartito.
 * El grafo g contiene los vecinos de la particion izquierda.
 * r debe inicializarse con tamano m (particion derecha) lleno de -1.
 * Retorna el tamano del matching y r[v] almacena el nodo izquierdo asignado (-1 si ninguno).
 * Uso:
 * vi r(m, -1);
 * int matching = hopcroftKarp(g, r);
 * Tiempo: O(E\sqrt{V})
 */

int hopcroftKarp(vector<vi>& g, vi& r) {
  int n = SZ(g), res = 0;
  vi l(n, -1), q(n), d(n);
  auto dfs = [&](auto f, int u) -> bool {
    int t = exchange(d[u], 0) + 1;
    for (int v : g[u])
      if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
        return l[u] = v, r[v] = u, 1;
    return 0;
  };
  for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
    FOR (i, 0, n) if (l[i] == -1) q[t++] = i, d[i] = 1;
    FOR (i, 0, t) for (int v : g[q[i]]) {
      if (r[v] == -1) f = 1;
      else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
    }
    if (!f) return res;
    FOR (i, 0, n) if (l[i] == -1) res += dfs(dfs, i);
  }
}
