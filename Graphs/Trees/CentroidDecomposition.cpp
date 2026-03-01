/**
 * Descripcion: descompone un arbol recursivamente 
 * eliminando su centroide, formando el "Arbol de Centroides" (CD).
 * Propiedades clave del CD:
 *   1. Su altura maxima es log(V).
 *   2. Para cualquier par de nodos (u, v) en el arbol original, 
 *      el LCA(u, v) en el CD es un nodo en el camino de u a v.
 * `fat[u]` guarda el padre de `u` en el CD (-1 si es la raiz).
 * (Tip: Usar vector<basic_string<int>> en lugar de vector<vector<int>> 
 * para la lista de adyacencia puede mejorar los tiempos por SSO).
 * Tiempo: O(V log V)
 * Status: testeado en Codeforces 321C
 */
struct CD {
  int n;
  vector<vector<int>> adj;
  vector<int> sz, fat;
  vector<bool> tk;

  CD(const vector<vector<int>>& adj) : n(SZ(adj)), adj(adj), sz(n), fat(n, -1), tk(n, false) {
    decompose(0, getSz(0, -1));
  }

  int getSz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p && !tk[v]) sz[u] += getSz(v, u);
    return sz[u];
  }

  void decompose(int u, int globalSz, int p = -1) {
    for (int v : adj[u]) if (!tk[v] && 2 * sz[v] >= globalSz) {
      sz[u] = 0;
      decompose(v, globalSz, p);
      return;
    }
    tk[u] = true;
    fat[u] = p;
    for (int v : adj[u]) if (!tk[v]) decompose(v, getSz(v, -1), u);
  }
};