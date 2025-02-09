/**
 * Descripcoin: encuentra todos los componentes biconectados de un 
 * grafo no dirigido y corre un callback para las aristas de cada uno.
 * En un componente biconectado existen al menos 2 caminos distintos
 * entre cada par de nodos. Importante notar que un nodo puede estar en
 * varios componentes. Una arista que no esta en un componente, es un
 * puente, puesto que no pertenece a ningun ciclo.
 * Uso:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vector<int>\& edgelist) {...});
 * Tiempo: O(E + V)
 */

vector<int> num, st;
vector<vector<pair<int, int>>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, top = me;
	for (auto [y, e] : ed[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ }
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	for (int i = 0; i < int(ed.size()); ++i) {
    if (!num[i]) {
      dfs(i, -1, f);
    }
  }
}