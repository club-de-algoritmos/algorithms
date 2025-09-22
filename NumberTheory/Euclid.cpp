/**
 * Descripcion: Algoritmo extendido de Euclides,
 * retorna gcd(a, b) y encuentra dos enteros
 * (x, y) tal que ax + by = gcd(a, b), si solo
 * necesitas el gcd, utiliza __gcd (c++14 o
 * anteriores) o gcd (c++17 en adelante)
 * Si a y b son coprimos, entonces x es el
 * inverso de a mod b
 * Tiempo: O(log n)
 */

int euclid(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  int d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}