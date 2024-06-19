/**
 * Descripcion: Calcula a^b mod m
 * Tiempo: O(log b)
 */
ll be(ll a, ll b, ll m) {
  ll res = 1;
  a %= m;
  while (b) {
    if (b & 1) {
      res = res * a % m;
    }
    a = a * a % m;
    b >>= 1;
  }
  return res;
}