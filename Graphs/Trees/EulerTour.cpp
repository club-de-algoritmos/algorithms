/**
 * Descripcion: utilizando una DFS, es posible aplanar un arbol,
 * esto se logra guardando en que momento entra y sale cada nodo,
 * apoyandonos de una estructura para consultas de rango es muy
 * util para consultas sobre un subarbol: saber la suma de
 * todos los nodos en el, el nodo con menor valor, etc.
 * Tiempo: O(n)
 */

vi g[MAXN];
int val[MAXN], in[MAXN], out[MAXN], toursz = 0;
void dfs(int u, int p) {
  in[u] = toursz++;

  for (auto& v : g[u])
    if (v != p)
      dfs(v, u);

  out[u] = toursz++;
}