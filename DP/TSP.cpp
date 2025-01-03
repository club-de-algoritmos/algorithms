/**
 * Descripcion: algoritmo para resolver el problema del viajero (TSP):
 * consiste en encontrar un recorrido que visite todos los vertices del
 * grafo, sin repeticiones y con el costo minimo. Este codigo resuelve
 * una variante del TSP donde se puede comenzar en cualquier vertice y
 * no necesita volver al inicial.
 * Tiempo: O(2^n * n)
 */

constexpr int MAX_NODES = 15;
int n, dist[MAX_NODES][MAX_NODES], dp[MAX_NODES][1 << (MAX_NODES + 1)];

int solve(int i, int mask) {
  if (mask == (1 << n) - 1) {
    return 0;
  }
  int &ans = dp[i][mask];
  if (ans != -1) {
    return ans;
  }
  ans = INF;
  for (int notVisMask = (1 << n) - 1 - mask; notVisMask; notVisMask &= notVisMask - 1) {
    int j = __builtin_ctz(notVisMask);
    ans = min(ans, solve(j, mask | (1 << j)) + dist[i][j]);
  }
  return ans;
}

int solveTSP() {
  int ans = INF;
  for (int i = 0; i < n; i++)
    ans = min(ans, solve(i, (1 << (i))));
  return ans;
}

int iterativeTSP(vector<int>& dist) {
  int n = (int)dist.size();
  vector<vector<int>> dp(n, vector<int>(1 << n, INF));
  for (int i = 0; i < n; ++i) {
    dp[i].back() = 0;
  }
  for (int mask = (1 << n) - 2; mask; --mask) {
    for (int visMask = mask; visMask; visMask &= visMask - 1) {
      int i = __builtin_ctz(visMask);
      for (int notVisMask = (1 << n) - 1 - mask; notVisMask; notVisMask &= notVisMask - 1) {
        int j = __builtin_ctz(notVisMask);
        dp[i][mask] = min(dp[i][mask], dist[i][j] + dp[j][mask | (1 << j)]);
      }
    }
  }
  int ans = INF;
  for (int i = 0; i < n; ++i) {
    ans = min(ans, dp[i][1 << i]);
  }
  return ans;
}
