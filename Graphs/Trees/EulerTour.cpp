/**
 * Descripcion: utilizando una DFS, es posible aplanar un arbol,
 * esto se logra guardando en que momento entra y sale cada nodo,
 * apoyandonos de una estructura para consultas de rango es muy
 * util para consultas sobre un subarbol: saber la suma de
 * todos los nodos en el, el nodo con menor valor, etc.
 * Tiempo: O(n)
 */
vector<vi> g[maxn];
int in[maxn], out[maxn], t = 0;
void dfs(int u, int p) {
  in[u] = ++t;
  for (auto& v:g[u])if(v!=p)dfs(v,u);
  out[u] = t;
}