/**
 * Descripcion: sirve para la busqueda de componentes
 * fuertemente conexos (SCC), este realiza dos pasadas DFS,
 * la primera para almacenar el orden de finalizacion
 * decreciente (orden topologico) y la segunda se realiza en
 * un grafo transpuesto a partir del orden topologico para
 * hallar los SCC. Retorna el vector de los SCC, donde
 * SCC[i] es el vector de los nodos del i-esimo SCC
 * Tiempo: O(V + E)
 */
vector<vi> korasaju(vector<vi>& g, vector<vi>& gT) {
  int n = SZ(g), pass = 1;
  vector<vi> scc;
  vi last_vis(n, 0), S;
  auto dfs = [&](auto self, int u) -> void {
    if (pass == 2) scc.back().pb(u);
    last_vis[u] = pass;
    for (auto v : pass == 1 ? g[u] : gT[u])
      if (last_vis[v] != pass) self(self, v);
    if (pass == 1) S.pb(u);
  };
  FOR(u, 0, n) if (last_vis[u] != pass) dfs(dfs, u);
  pass = 2;
  reverse(ALL(S));
  for (auto& u : S)
    if (last_vis[u] != pass) {
      scc.pb({});
      dfs(dfs, u);
    }
  return scc;
}
