/*
 * Descripcion: el logaritmo discreto es un entero x
 * que satisface la ecuacion a**x = b (mod m). Dados
 * los enteros a, b, y m, se busca a x.
 * Este problema se puede resolver con el algoritmo
 * de meet-in-the-middle Baby-step giant-step.
 * Nota. Si hay varios argumentos p que mapean el mismo
 * valor f_1, solo se guarda uno de ellos. Esto funciona
 * porque solo buscamos una posible solucion, pero, si se
 * necesitan todas, se puede cambiar map<int, int> a algo
 * como map<int, vector<int>>. Luego, sigue adaptar el
 * segundo paso de manera correspondiente.
 * Tiempo:
 *  O(\sqrt{N} log n) - metodo 1
 *  O(\sqrt{N}) - metodo 2 (amortizado con unordered_map)
 *  O(\sqrt{N}) - metodo 3, usado cuando a y m no son coprimos
 */

int solve(int a, int b, int m) {
  /* Se asume que 0**0 = 1, si se usan otras convenciones,
   * manejar caso a = 0 aparte, con
   * if (a == 0)
   *     return b == 0 ? 1 : -1;
   */
  a %= m, b %= m;
  int n = sqrt(m) + 1;
  map<int, int> vals;
  for (int p = 1; p <= n; ++p) {
    vals[be(a, p * n, m)] = p;
  }
  for (int q = 0; q <= n; ++q) {
    int cur = be(a, q, m) * 1ll * b % m;
    if (vals.count(cur)) {
      int ans = vals[cur] * n - q;
      return ans;
    }
  }
  return -1;
}

int solve(int a, int b, int m) {
  a %= m, b %= m;
  int n = sqrt(m) + 1;

  int an = 1;
  for (int i = 0; i < n; ++i) {
    an = (an * 1ll * a) % m;
  }

  unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }

  for (int p = 1, cur = 1; p <= n; ++p) {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur)) {
      int ans = n * p - vals[cur];
      return ans;
    }
  }
  return -1;
}

int solve(int a, int b, int m) {
  a %= m, b %= m;
  int k = 1, add = 0, g;
  while ((g = gcd(a, m)) > 1) {
    if (b == k) {
      return add;
    }
    if (b % g) {
      return -1;
    }
    b /= g, m /= g, ++add;
    k = (k * 1ll * a / g) % m;
  }

  int n = sqrt(m) + 1;
  int an = 1;
  for (int i = 0; i < n; ++i) {
    an = (an * 1ll * a) % m;
  }

  unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }

  for (int p = 1, cur = k; p <= n; ++p) {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur)) {
      int ans = n * p - vals[cur] + add;
      return ans;
    }
  }
  return -1;
}