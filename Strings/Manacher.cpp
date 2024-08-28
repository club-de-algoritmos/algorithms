/*
 * Descripcion: para cada posicion de un string, calcula:
 * p[0][i] = la mitad de la longitud del palindromo par
 * mas grande alrededor de la posicion i
 * p[1][i] = la longitud del palindromo impar mas grande
 * alrededor de la posicion i (la mitad redondeado hacia abajo)
 * Tiempo: O(N)
 */

array<vi, 2> manacher(const string& s) {
  int n = SZ(s);
  array<vi, 2> p = {vi(n + 1), vi(n)};
  FOR(z, 0, 2)
  for (int i = 0, l = 0, r = 0; i < n; i++) {
    int t = r - i + !z;
    if (i < r) p[z][i] = min(t, p[z][l + t]);
    int L = i - p[z][i], R = i + p[z][i] - !z;
    while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
      p[z][i]++, L--, R++;
    if (R > r) l = L, r = R;
  }
  return p;
}