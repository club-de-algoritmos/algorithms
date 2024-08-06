/**
 * Descripcion: Utilizando el metodo de ModOperations.cpp, calculamos de manera
 * eficiente los inversos modulares de x (arreglo inv) y de x! (arreglo invfact),
 * para toda x < MAX, se utiliza el hecho de que comb(n, k) = (n!) / (k! * (n - k)!)
 * Tiempo: O(MAX) en el precalculo de inversos modulares y O(1) por query.
 */

#include "ModInverse.h";

ll invfact[maxn];
void precalc_invfact() {
  precalc_inv();
  invfact[1] = 1;
  for (int i = 2; i < maxn; i++) invfact[i] = invfact[i - 1] * inv[i] % MOD;
}

ll comb(int n, int k) {
  if (n < k) return 0;
  return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

/**
 * Descripcion: Se basa en el teorema de lucas, se puede utilizar cuando tenemos
 * una MAX larga y un modulo m relativamente chico.
 * Tiempo: O(m log_m(n))
 */
ll comb(int n, int k) {
  if (n < k || k < 0) return 0;
  if (n == k) return 1;
  return comb(n % MOD, k % MOD) * comb(n / MOD, k / MOD) % MOD;
}

/*
 * Descripcion: precalculo de combinaciones
 * Tiempo: O(n^2)
 */
ll c[maxn][maxk];
void calc_comb() {
  FOR(i, 0, MAX_N) {
    c[i][0] = c[i][i] = 1;
    FOR(j, 1, i) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }
}