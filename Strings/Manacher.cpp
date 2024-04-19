/*
 * Descripcion: longitud del palindromo mas grande centrado
 * en cada caracter de la cadena y entre cada par
 * consecutivo
 * Tiempo: O(n)
 */

vi manacher(string _S) {
  string S = char(64);
  for (char c : _S) S += c, S += char(35);
  S.back() = char(38);
  vi ans(SZ(S) - 1);
  int lo = 0, hi = 0;
  FOR(i, 1, SZ(S) - 1) {
    if (i != 1) ans[i] = min(hi - i, ans[hi - i + lo]);
    while (S[i - ans[i] - 1] == S[i + ans[i] + 1]) ++ans[i];
    if (i + ans[i] > hi) lo = i - ans[i], hi = i + ans[i];
  }
  ans.erase(begin(ans));
  FOR(i, 0, SZ(ans))
  if (i % 2 == ans[i] % 2) ++ans[i];
  return ans;
}