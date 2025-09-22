/*
 * Descripcion: resolvedor de sistemas de ecuaciones lineales.
 * a[i] = coeficientes de la i-esima ecuacion, a[i][m] es su suma.
 * Retorna el numero de soluciones.
 * Recibe como referencia el vector solucion. Encuentra cualquiera.
 * El primer metodo funciona igual sobre modulo, sin necesitar las
 * heuristicas. Usar mint.
 * Caso especial: si se trabaja modulo 2, A - B = A xor B. Por lo tanto,
 * se puede usar bitset para optimizar el pivoteo a O(n^3/64)
 * Tiempo: O(n^3)
 */

int gauss(vector<vector<double>> &a, vector<double> &ans) {
  int n = int(a.size()), m = int(a[0].size()) - 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i)
      if (abs(a[i][col]) > abs(a[sel][col]))
        sel = i;
    if (abs(a[sel][col]) < EPS) continue;

    for (int i = col; i <= m; ++i) swap(a[sel][i], a[row][i]);
    where[col] = row;

    for (int i = 0; i < n; ++i) if (i != row) {
      double c = a[i][col] / a[row][col];
      for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
    }
    ++row;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; ++i) if (where[i] != -1)
    ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > EPS) return 0;
  }

  for (int i = 0; i < m; ++i) if (where[i] == -1) return INF;

  return 1;
}