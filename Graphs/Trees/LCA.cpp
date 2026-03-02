/**
 * Descripcion: ancestro comun mas bajo (LCA) usando 
 * binary lifting. Responde consultas en O(log n).
 * Tiempo: O(n log n) en construccion, O(log n) por consulta.
 * (Tip: Usar vector<basic_string<int>> en lugar de vector<vector<int>>
 * para la lista de adyacencia puede mejorar el tiempo por SSO).
 * Uso:
 *   LCA lca(adj);
 *   int ans = lca.query(u, v);
 * Status: testeado en ICPC LATAM 2017 - Imperial Roads 
 */
struct LCA {
  int n, maxlog;
  vector<vector<int>> jmp;
  vector<int> d;

  LCA(const vector<vector<int>>& adj, int root = 0) {
    n = SZ(adj);
    maxlog = __lg(n) + 2;
    jmp.assign(maxlog, vector<int>(n, -1));
    d.assign(n, 0);
    auto dfs = [&](auto& self, int u, int p) -> void {
      jmp[0][u] = p;
      for (int i = 1; i < maxlog; i++) {
        if (jmp[i - 1][u] != -1) {
          jmp[i][u] = jmp[i - 1][jmp[i - 1][u]];
        }
      }
      for (int v : adj[u]) {
        if (v != p) {
          d[v] = d[u] + 1;
          self(self, v, u);
        }
      }
    };
    dfs(dfs, root, -1);
  }

  int query(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int dist = d[u] - d[v];
    for (int i = maxlog - 1; i >= 0; i--) {
      if ((dist >> i) & 1) u = jmp[i][u];
    }
    if (u == v) return u;
    for (int i = maxlog - 1; i >= 0; i--) {
      if (jmp[i][u] != jmp[i][v]) {
        u = jmp[i][u];
        v = jmp[i][v];
      }
    }
    return jmp[0][u];
  }

  int dist(int u, int v) { 
    return d[u] + d[v] - 2 * d[query(u, v)]; 
  }
};