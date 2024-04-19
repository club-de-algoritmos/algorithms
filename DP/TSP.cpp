/**
 * Descripcion: algoritmo para resolver el problema del
 * viajero (TSP): consiste en encontrar un recorrido que
 * visite todos los vertices del grafo, sin repeticiones y
 * con el costo minimo. Este codigo resuelve una variante
 * del TSP donde se puede comenzar en cualquier vertice y no
 * necesita volver al inicial.
 * Tiempo: O(2^n * n)
 */

constexpr int MAX_NODES = 15;
int n, dist[MAX_NODES][MAX_NODES],
    dp[MAX_NODES][1 << (MAX_NODES + 1)];

int solve(int i, int mask) {
  if (mask == (1 << n) - 1) return 0;
  int &ans = dp[i][mask];
  if (ans != -1) return ans;

  ans = INF;
  for (int k = 0; k < n; k++)
    if ((mask & (1 << k)) == 0)
      ans =
          min(ans, solve(k, mask | (1 << k)) + dist[i][k]);
  return ans;
}

int solveTSP() {
  int ans = INF;
  for (int i = 0; i < n; i++)
    ans = min(ans, solve(i, (1 << (i))));
  return ans;
}
