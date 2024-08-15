/**
 * Descripcion: calcula el costo minimo para ir de un nodo hacia todos los
 * demas alcanzables. Puede detectar ciclos negativos, dando una ultima
 * pasada y revisando si alguna distancia se acorta.
 * Tiempo: O(VE)
 */

void bellmanFord(vector<array<int, 3>>& e, int n) {
  vi d(n, INF); d[x] = 0;
  for (int i=0;i<n;i++)for(auto& [u, v, w]:e)d[v]=min(d[v],d[u]+w);
  for(auto& [u, v, w]:e)if(d[u]!=INF&&d[u]+w<d[v]) {
// neg cycle: all nodes reachable from u have -INF distance. To reconstruct
// neg cycle save "prev" of each node, go up from u until repeating a node.
// this node and all nodes between the two occurences form a neg cycle
  }
}
