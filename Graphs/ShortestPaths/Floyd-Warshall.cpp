/**
 * Descripcion: algoritmo de Floyd-Warshall para calcular la
 * minima distancia entre cada par de nodos, si no se requiere
 * recalcular el camino, ignorar p.
 * Retorna un par (g, p), en donde g es una matriz modificada
 * en la que g[i][j] es el costo minimo para llegar desde el
 * nodo i al nodo j y p es el nodo anterior en dicho camino,
 * utilizado para recalcular la ruta.
 * Tiempo: O(V^3)
 */

pair<vector<vi>, vi> floydWarshall(vector<vi> g) {
  int n = SZ(g);
  vector<vi> p(n, vi(n));
  FOR (i, 0, n) FOR (j, 0, n) p[i][j] = i;
  FOR(k,0,n)FOR(i,0,n)FOR(j,0,n)if(g[i][k]+g[k][j]<g[i][j]){
    p[i][j] = p[k][j];
    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
  }
  return {g, p};
}
void printPath(vector<vi>& p, int i, int j) {
  if (i != j) printPath(p, i, p[i][j]);
  cout << j << " ";
}
