/**
 * Descripcion: Encuentra todos los componentes biconectados
 * en un grafo no dirigido y ejecuta un callback f para las aristas de cada uno.
 * Una arista que no pertenece a ningun componente es un puente.
 * Soporta multiaristas usando IDs unicos por arista.
 * Uso:
 * vector<vector<pi>> ed(n);
 * // para cada arista i entre (u, v): ed[u].pb({v, i}); ed[v].pb({u, i});
 * bicomps(ed, [&](const vi& edge_list) { ... });
 * Tiempo: O(V + E)
 */

template <class F>
void bicomps(vector<vector<pi>>& ed, F f) {
  int n = SZ(ed), Time = 0;
  vi num(n), st;
  auto dfs = [&](auto& self, int at, int par) -> int {
    int me = num[at] = ++Time, top = me;
    for (auto [y, e] : ed[at]) if (e != par) {
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me) st.pb(e);
      } else {
        int si = SZ(st);
        int up = self(self, y, e);
        top = min(top, up);
        if (up == me) {
          st.pb(e);
          f(vi(begin(st) + si, end(st)));
          st.resize(si);
        } else if (up < me) {
          st.pb(e);
        }
      }
    }
    return top;
  };
  FOR (i, 0, n) if (!num[i]) dfs(dfs, i, -1);
}
