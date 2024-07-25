/**
 * Descripcion: Algoritmo extendido de Euclides, retorna gcd(a, b) y encuentra
 * dos enteros (x, y) tal que ax + by = gcd(a, b), si solo necesitas
 * el gcd, utiliza __gcd (c++14 o anteriores) o gcd (c++17 en adelante)
 * Si a y b son coprimos, entonces x es el inverso de a mod b
 * Tiempo: O(log n)
 */

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}