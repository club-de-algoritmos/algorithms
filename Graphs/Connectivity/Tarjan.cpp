/**
 * Descripcion: sirve para la busqueda de componentes
 * fuertemente conexos (SCC) Un SCC se define de la
 * siguiente manera: si elegimos cualquier par de vertices u
 * y v en el SCC, podemos encontrar un camino de u a v y
 * viceversa Explicacion: La idea basica del algoritmo de
 * Tarjan es que los SCC forman subarboles en el arbol de
 * expansion de la DFS. Ademas de calcular tin(u) y low(u)
 * para cada vertice, anadimos el vertice u al final de una
 * pila y mantenemos la informacion de que vertices estan
 * siendo explorados, mediante vi vis. Solo los vertices que
 * estan marcados como vis (parte del SCC actual) pueden
 * actualizar low(u). Ahora, si tenemos el vertice u en este
 * arbol de expansion DFS con low(u) = tin(u), podemos
 * concluir que u es la raiz de un SCC y los miembros de
 * estos SCC se pueden identificar obteniendo el contenido
 * actual de la pila, hasta que volvamos a llegar al vertice
 * u. Retorna el vector de los SCC, donde SCC[i] es el
 * vector de los nodos del i-esimo SCC
 * Tiempo: O(V + E)
 */
vector<vi> tarjan(vector<vi>& g) {
  int n = SZ(g), timer = 0;
  vector<vi> scc;
  vi tin(n, -1), low(n, 0), vis(n, 0);
  stack<int> st;
  auto dfs = [&](auto self, int u) -> void {
    tin[u] = low[u] = timer++;
    st.push(u);
    vis[u] = 1;
    for (int v : g[u]) {
      if (tin[v] == -1) self(self, v);
      if (vis[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == tin[u]) {
      scc.pb({});
      while (1) {
        int v = st.top();
        st.pop();
        vis[v] = 0;
        scc.back().pb(v);
        if (u == v) break;
      }
    }
  };
  FOR(i, 0, n) if (tin[i] == -1) dfs(dfs, i);
  return scc;
}
