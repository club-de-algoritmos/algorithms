/*
 * Descripcion: Dado un sistema de N ecuaciones lineales con
 * M incognitas, determinar si existe solucion, infinitas
 * soluciones o en caso de que halla al menos una, encontrar
 * cualquiera de ellas.
 * Tiempo: O(n^3)
 */

int gauss(vector<vector<double>> &a, vector<double> &ans) {
  int n = SZ(a), m = SZ(a[0]) - 1;
  vi where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    FOR(i, row, n)
    if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if (abs(a[sel][col]) < EPS) continue;

    FOR(i, col, m + 1)
    swap(a[sel][i], a[row][i]);
    where[col] = row;

    FOR(i, 0, n) {
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; ++j)
          a[i][j] -= a[row][j] * c;
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  FOR(i, 0, m) {
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];
  }
  FOR(i, 0, n) {
    double sum = 0;
    FOR(j, 0, m)
    sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > EPS) return 0;
  }

  FOR(i, 0, m)
  if (where[i] == -1) return 1e9;  /// infinitas soluciones
  return 1;
}

// Gauss con MOD
// Nota: es necesario la funcion modInverse
// Si MOD = 2, se convierte en operacion XOR y se puede
// utilizar un bitset para construir la ecuacion (disminuye
// la complejidad)
ll gaussMod(vector<vi> &a, vi &ans) {
  ll n = SZ(a), m = SZ(a[0]) - 1;
  vi where(m, -1);
  for (ll col = 0, row = 0; col < m && row < n; ++col) {
    ll sel = row;
    FOR(i, row, n)
    if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if (abs(a[sel][col]) <= EPS) continue;

    FOR(i, col, m + 1)
    swap(a[sel][i], a[row][i]);
    where[col] = row;

    FOR(i, 0, n) {
      if (i != row) {
        ll c =
            1LL * a[i][col] * modInverse(a[row][col]) % MOD;
        for (ll j = col; j <= m; ++j)
          a[i][j] = (MOD + a[i][j] -
                     (1LL * a[row][j] * c) % MOD) %
                    MOD;
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  FOR(i, 0, m) {
    if (where[i] != -1)
      ans[i] = 1LL * a[where[i]][m] *
               modInverse(a[where[i]][i]) % MOD;
  }
  FOR(i, 0, n) {
    ll sum = 0;
    FOR(j, 0, m)
    sum = (sum + 1LL * ans[j] * a[i][j]) % MOD;
    if (abs(sum - a[i][m]) > EPS) return 0;
  }

  FOR(i, 0, m)
  if (where[i] == -1) return 1e9;  /// infinitas soluciones
  return 1;
}