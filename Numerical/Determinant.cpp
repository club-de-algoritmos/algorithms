/*
 * Descripcion: Calcula la determinante de la matriz.
 * Nota: La matriz se modifica
 * Tiempo: O(n^3)
 */

double det(vector<vector<double>>& a) {
  int n = SZ(a);
  double res = 1;
  FOR(i, 0, n) {
    int b = i;
    FOR(j, i + 1, n) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
    if (i != b) swap(a[i], a[b]), res *= -1;
    res *= a[i][i];
    if (res == 0) return 0;
    FOR(j, i + 1, n) {
      double v = a[j][i] / a[i][i];
      if (v != 0) FOR(k, i + 1, n) a[j][k] -= v * a[i][k];
    }
  }
  return res;
}

// Determinante con modulo
// Si se elimina el modulo obtendras la version de solo enteros
ll detMod(vector<vector<ll>>& a, int mod) {
  int n = SZ(a);
  ll ans = 1;
  FOR(i, 0, n) {
    FOR(j, i + 1, n) {
      while (a[j][i] != 0) {
        ll t = a[i][i] / a[j][i];
        if (t) FOR(k, i, n)
        a[i][k] = (a[i][k] - a[j][k] * t) % mod;
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
}