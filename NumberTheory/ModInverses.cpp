/**
 * Descripcion: Precalculo de modulos inversos hasta n.
 * Tiempo: O(n)
 */
vector<mint> precalc_inverses(int n) {
  vector<mint> inv(n);
  inv[1] = 1;
  for (int i = 2; i < n; ++i) {
    inv[i] = inv[MOD%i] * (MOD/i) * -1;
  }
  return inv;
}