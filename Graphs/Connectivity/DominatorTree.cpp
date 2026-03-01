/**
 * Descripcion: Construye el arbol de dominadores para un grafo dirigido dado 
 * un nodo raiz. Un nodo 'u' domina a un nodo 'v' si todos los caminos desde 
 * la raiz hasta 'v' deben pasar obligatoriamente por 'u'. El dominador 
 * inmediato de un nodo 'v' es el unico nodo 'u' que domina a 'v' y no domina 
 * a ningun otro dominador de 'v', siendo asi su padre directo en el arbol.
 * Uso:
 *  vi iDom = getDominatorTree(adj, root);
 *      donde iDom[u] es el dominador inmediato del nodo u
 * Tiempo: O((V + E) log V)
 */

vi getDominatorTree(const vector<vi>& adj, int r) {
  int n = SZ(adj), t = 0;
  vi id(n, -1), rId(n), relabeledP(n, -1);
  vector<vi> rAdj(n);
  auto eulerTour = [&](auto&& self, int u) -> void {
    id[u] = t++;
    rId[id[u]] = u;
    for (int v : adj[u]) {
      if (id[v] == -1) {
        relabeledP[v] = id[u];
        self(self, v);
      }
      rAdj[v].pb(u);
    }
  };
  eulerTour(eulerTour, r);
  
  vi dsuP(t);
  vector<pi> dsuW(t, {INT_MAX, -1});
  iota(dsuP.begin(), dsuP.end(), 0);
  auto query = [&](auto&& self, int u) -> pi {
    if (dsuP[u] == u) return dsuW[u];
    dsuW[u] = min(dsuW[u], self(self, dsuP[u]));
    dsuP[u] = dsuP[dsuP[u]];
    return dsuW[u];
  };
 
  vi sDom(t, INT_MAX), iDom(n, -1);
  vector<vi> pending(t);
  ROF (i, t, 0) {
    for (int j : pending[i]) {
      auto [mn, k] = query(query, j);
      iDom[rId[j]] = mn == sDom[j] ? rId[sDom[j]] : rId[k];
    }
    if (!i) break;
    int u = rId[i];
    for (int v : rAdj[u]) {
      int j = id[v];
      sDom[i] = min(sDom[i], j < i ? j : query(query, j).first);
    }
    dsuW[i] = {sDom[i], i}; 
    dsuP[i] = relabeledP[u];
    pending[sDom[i]].pb(i);
  }
  FOR (i, 1, t) {
    int u = rId[i];
    if (iDom[u] != rId[sDom[i]]) iDom[u] = iDom[iDom[u]];
  }
  return iDom;
}