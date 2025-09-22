/*
 * Descripcion: Calcula la determinante de la matriz.
 * Nota: La matriz se modifica
 * Tiempo: O(n^3)
 */

double det(vector<vector<double>>& a) {
  int n = SZ(a);
  double res = 1;
  for (int i = 0; i < n; ++i) {
    int b = i;
    for (int j = i + 1; j < n; ++j) 
      if (abs(a[j][i]) > abs(a[b][i]))
        b = j;
    if (i != b) swap(a[i], a[b]), res *= -1;
    res *= a[i][i];
    if (res == 0) return 0;
    for (int j = i + 1; j < n; ++j) {
      double v = a[j][i] / a[i][i];
      if (v != 0)
        for (int k = i + 1; k < n; ++k)
          a[j][k] -= v * a[i][k];
    }
  }
  return res;
}

// Determinante con modulo.
// Sin el mod se obtiene la version de solo enteros.
mint detMod(vector<vector<mint>>& a) {
  int n = int(a.size());
  mint ans = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      while (a[j][i] != 0) {
        ll t = a[i][i] / a[j][i];
        if (t) 
          for (int k = i; k < n; ++k)
            a[i][k] -= a[j][k] * t;
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans *= a[i][i];
    if (!ans.v) return 0;
  }
  return ans;
}