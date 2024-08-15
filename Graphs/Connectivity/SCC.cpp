/**
 * Descripcion: algoritmo de Tarjan para la busqueda de 
 * componentes fuertemente conexos (SCC)
 * Idea: Los SCC forman subarboles en el arbol de expansion de
 * la DFS. Ademas de calcular tin(u) y low(u) para cada vertice, 
 * se agrega el vertice u al final de una pila z y mantenemos la 
 * informacion de que vertices estan siendo explorados, mediante
 * vi vis. Solo los vertices visitados (parte del SCC actual) 
 * pueden actualizar low(u). Si low(u) = tin(u), u es la raiz de
 * un SCC y sus miembros pueden obtenerse sacando de la pila.
 * Retorna un vector, donde scc[u] es el indice de su SCC.
 * Tiempo: O(V + E)
 */
vi scc(vector<vi>& g) {
  int n = SZ(g), t = 0, ncomps = 0;
  vi tin(n), scc(n, -1), z;
  auto dfs = [&](auto&& self, int u) -> int {
    int low = tin[u] = ++t, x; z.push_back(u);
    for (auto v : g[u]) if (scc[v] < 0)
      low = min(low, tin[v] ?: self(self, v));
    if (low == tin[u]) {
      do {
        x = z.back(); z.pop_back();
        scc[x] = ncomps;
      } while (x != u);
      ncomps++;
    }
    return tin[u] = low;
  };
  FOR (i, 0, n) if (scc[i] == -1) dfs(dfs, i);
  return scc;
}
