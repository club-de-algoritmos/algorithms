/**
 * Descripcion : Calcula a * b mod m para
 * cualquier 0 <= a, b <= c <= 7.2 * 10^18
 * Tiempo: O(1)
 */
using ull = unsigned long long;
ull modmul(ull a, ull b, ull m) {
  ll ret = a * b - m * ull(1.L / m * a * b);
  return ret + m * (ret < 0) - m * (ret >= (ll)m);
}
