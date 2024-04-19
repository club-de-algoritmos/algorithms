/*
 * Descripcion: La Z-function es un arreglo donde el
 * elemento i es igual al numero mas grande de caracteres
 * que empiezan desde la posicion i que coincide con el
 * prefijo de S, excepto Z[0] = 0. (abacaba -> 0010301)
 * Tiempo: O(|S|)
 */
vi Z(const string& S) {
  vi z(SZ(S));
  int l = -1, r = -1;
  FOR(i, 1, SZ(S)) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (i + z[i] < SZ(S) && S[i + z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}