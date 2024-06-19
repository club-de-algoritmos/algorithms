/*
 * Teorema del Resto Chino (CRT)
 * Descripcion: Encuentra x dentro de un sistema lineal
 * de congruencias tal que:
 * x =_ a (mod n)
 * x =_ b (mod m)
 * Se asume que n*m < 2^62
 * Tiempo: O(log n)
 */

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  assert((a - b) % g == 0);  // else no solution
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}