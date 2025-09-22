/**
 * Descripcion: calculo de combinaciones.
 * El primer metodo utiliza la formula convencional
 * y el segundo se  basa en el teorema de lucas, que
 * se usa con n grande y MOD chico.
 * Tiempo 1: O(n) de precalculo y O(1) por query.
 * Tiempo 2: O(m log_m(n))
 */

#include "ModInverses.h";

vector<mint> precalc_invfact(int n) {
  vector<mint> inv = precalc_inverses(n), invFact(n);
  invFact[0] = 1;
  for (int i = 1; i < n; i++)
    invfact[i] = invfact[i - 1] * inv[i];
}

mint comb(int n, int k) {
  return n < k ? 0 : fact[n]*invfact[k]*invfact[n - k];
}

mint comb(int n, int k) {
  if (n < k || k < 0) return 0;
  if (n == k) return 1;
  return comb(n % MOD, k % MOD) * comb(n / MOD, k / MOD);
}