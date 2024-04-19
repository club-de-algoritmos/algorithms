/**
 * Descripcion: modifica la matriz de adyacencia
 * graph[n][n], tal que graph[i][j] pasa a indicar el costo
 * minimo para ir desde el nodo i al j
 * Tiempo: O(n^3)
 */
int graph[MAXN][MAXN];
int p[MAXN][MAXN];  // Guardar camino

void floydWarshall() {
  FOR(i, 0, N) {  // Inicializar el camino
    FOR(j, 0, N) { p[i][j] = i; }
  }

  FOR(k, 0, N) {
    FOR(i, 0, N) {
      FOR(j, 0, N) {
        if (graph[i][k] + graph[k][j] <
            graph[i][j])  // Solo utilizar si necesitas el
                          // camino
          p[i][j] = p[k][j];

        graph[i][j] =
            min(graph[i][j], graph[i][k] + graph[k][j]);
      }
    }
  }
}

void printPath(int i, int j) {
  if (i != j) printPath(i, p[i][j]);
  cout << j << " ";
}
